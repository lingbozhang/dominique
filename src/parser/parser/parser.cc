/* Copyright 2020 The IntellGraph Authors. All Rights Reserved.
Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at
   http: //www.apache.org/licenses/LICENSE-2.0
Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

Contributor(s):
    Lingbo Zhang <lingboz2015@gmail.com>
==============================================================================*/
#include "src/parser/parser/parser.h"

#include "src/lexer/lexer.h"
#include "src/lexer/tag.h"
#include "src/lexer/token.h"
#include "src/parser/expr/access.h"
#include "src/parser/expr/and.h"
#include "src/parser/expr/arith.h"
#include "src/parser/expr/constant.h"
#include "src/parser/expr/expr.h"
#include "src/parser/expr/not.h"
#include "src/parser/expr/or.h"
#include "src/parser/expr/rel.h"
#include "src/parser/expr/unary.h"
#include "src/parser/stmt/break.h"
#include "src/parser/stmt/do.h"
#include "src/parser/stmt/else.h"
#include "src/parser/stmt/if.h"
#include "src/parser/stmt/seq.h"
#include "src/parser/stmt/set.h"
#include "src/parser/stmt/set_elem.h"
#include "src/parser/stmt/stmt.h"
#include "src/parser/stmt/while.h"
#include "src/symbol/array.h"
#include "src/symbol/env.h"
#include "src/symbol/type.h"
#include "src/util.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"

namespace intellgraph {
namespace parser {

Parser::Parser(std::unique_ptr<lexer::Lexer> lex)
    : llvm_context_(std::make_unique<llvm::LLVMContext>()),
      llvm_builder_(std::make_unique<llvm::IRBuilder<>>(*llvm_context_)),
      llvm_module_(std::make_unique<llvm::Module>("Dominiuqe", *llvm_context_)),
      lex_(std::move(lex)), top_(std::make_unique<symbols::Env>(nullptr)) {}

Parser::~Parser() = default;

void Parser::ReadCodes(const std::string& codes) {
  lex_->ReadCodes(codes);
  Move();
}

void Parser::Program() {
  std::unique_ptr<inter::Stmt> s = Block();
  int begin = s->NewLabel();
  int after = s->NewLabel();
  s->EmitLabel(begin);
  s->Gen(begin, after);
  s->EmitLabel(after);
}

void Parser::Move() { look_ = lex_->Scan(); }

void Parser::Error(const std::string& str) {
  std::cout << "Near line " + std::to_string(lex_->get_line_number()) + ": " +
                   str;
  exit(1);
}

void Parser::Match(int t) {
  if (look_->tag_ == t) {
    Move();
    return;
  };
  Error("Syntax error");
}

std::unique_ptr<inter::Stmt> Parser::Block() {
  Match('{');
  std::unique_ptr<symbols::Env> savedEnv = std::move(top_);
  top_ = std::make_unique<symbols::Env>(savedEnv.get());
  Decls();
  std::unique_ptr<inter::Stmt> s = Stmts();
  Match('}');
  top_ = std::move(savedEnv);
  return s;
}

void Parser::Decls() {
  while (look_->tag_ == lexer::tag::kBasic) {
    std::unique_ptr<symbols::Type> p = Type();
    std::unique_ptr<lexer::Token> tok = look_->Clone();
    int width = p->width_;
    Match(lexer::tag::kId);
    Match(';');
    std::unique_ptr<inter::Id> id = std::make_unique<inter::Id>(
        static_cast_unique_ptr<lexer::Word>(tok->Clone()), std::move(p), used_);
    top_->Put(*(static_cast<lexer::Word*>(tok.get())), std::move(id));
    used_ += width;
  }
}

std::unique_ptr<symbols::Type> Parser::Type() {
  std::unique_ptr<symbols::Type> p =
      static_cast_unique_ptr<symbols::Type>(look_->Clone());
  Match(lexer::tag::kBasic);
  if (look_->tag_ != '[') {
    return p;
  }
  return Dims(std::move(p));
}

std::unique_ptr<symbols::Type> Parser::Dims(std::unique_ptr<symbols::Type> p) {
  Match('[');
  std::unique_ptr<lexer::Token> tok = look_->Clone();
  Match(lexer::tag::kNum);
  Match(']');
  if (look_->tag_ == '[') {
    p = Dims(p->CloneType());
  }
  return std::make_unique<symbols::Array>(
      std::move(p), static_cast_unique_ptr<lexer::Num>(tok->Clone())->value_);
}

std::unique_ptr<inter::Stmt> Parser::Stmts() {
  if (look_->tag_ == '}') {
    return inter::Stmt::Null().Clone();
  }
  return std::make_unique<inter::Seq>(Stmt(), Stmts());
}

std::unique_ptr<inter::Stmt> Parser::Stmt() {
  std::unique_ptr<inter::Expr> x;
  std::unique_ptr<inter::Stmt> s, s1, s2;
  const inter::Stmt *savedStmt = nullptr;
  switch (look_->tag_) {
    case ';': {
      Move();
      return inter::Stmt::Null().Clone();
    }
    case lexer::tag::kIf: {
      Match(lexer::tag::kIf);
      Match('(');
      x = Bool();
      Match(')');
      s1 = Stmt();
      if (look_->tag_ != lexer::tag::kElse) {
        return std::make_unique<inter::If>(std::move(x), std::move(s1));
      }
      Match(lexer::tag::kElse);
      s2 = Stmt();
      return std::make_unique<inter::Else>(std::move(x), std::move(s1),
                                           std::move(s2));
    }
    case lexer::tag::kWhile: {
      std::unique_ptr<inter::While> while_node =
          std::make_unique<inter::While>();
      savedStmt = inter::Stmt::Enclosing();
      inter::Stmt::Enclosing() = while_node.get();
      Match(lexer::tag::kWhile);
      Match('(');
      x = Bool();
      Match(')');
      s1 = Stmt();
      while_node->Init(std::move(x), std::move(s1));
      inter::Stmt::Enclosing() = savedStmt;
      return while_node;
    }
    case lexer::tag::kDo: {
      std::unique_ptr<inter::Do> do_node = std::make_unique<inter::Do>();
      savedStmt = inter::Stmt::Enclosing();
      inter::Stmt::Enclosing() = do_node.get();
      Match(lexer::tag::kDo);
      s1 = Stmt();
      Match(lexer::tag::kWhile);
      Match('(');
      x = Bool();
      Match(')');
      Match(';');
      do_node->Init(std::move(x), std::move(s1));
      inter::Stmt::Enclosing() = savedStmt;
      return do_node;
    }
    case lexer::tag::kBreak: {
      Match(lexer::tag::kBreak);
      Match(';');
      return std::make_unique<inter::Break>();
    }
    case '{': {
      return Block();
    }
    default:
      return Assign();
  }
}

std::unique_ptr<inter::Stmt> Parser::Assign() {
  std::unique_ptr<inter::Stmt> stmt;
  std::unique_ptr<lexer::Token> token = look_->Clone();
  Match(lexer::tag::kId);
  const inter::Id* id = top_->Get(*(static_cast<lexer::Word*>(token.get())));
  if (id == nullptr) {
    Error(token->ToString() + " undeclared!");
  }
  if (look_->tag_ == '=') {
    Move();
    stmt =
        std::make_unique<inter::Set>(std::make_unique<inter::Id>(*id), Bool());
  } else {
    std::unique_ptr<inter::Access> x = Offset(id);
    Match('=');
    stmt = std::make_unique<inter::SetElem>(std::move(x), Bool());
  }
  Match(';');
  return stmt;
}

std::unique_ptr<inter::Expr> Parser::Bool() {
  std::unique_ptr<inter::Expr> x = Join();
  while (look_->tag_ == lexer::tag::kOr) {
    std::unique_ptr<lexer::Token> token = std::move(look_);
    Move();
    x = std::make_unique<inter::Or>(std::move(token), std::move(x), Join());
  }
  return x;
}

std::unique_ptr<inter::Expr> Parser::Join() {
  std::unique_ptr<inter::Expr> x = Equality();
  while (look_->tag_ == lexer::tag::kAnd) {
    std::unique_ptr<lexer::Token> token = std::move(look_);
    Move();
    x = std::make_unique<inter::And>(std::move(token), std::move(x),
                                     Equality());
  }
  return x;
}

std::unique_ptr<inter::Expr> Parser::Equality() {
  std::unique_ptr<inter::Expr> x = Rel();
  while (look_->tag_ == lexer::tag::kEq || look_->tag_ == lexer::tag::kNe) {
    std::unique_ptr<lexer::Token> token = std::move(look_);
    Move();
    x = std::make_unique<inter::Rel>(std::move(token), std::move(x), Rel());
  }
  return x;
}

std::unique_ptr<inter::Expr> Parser::Rel() {
  std::unique_ptr<inter::Expr> x = Expr();
  switch (look_->tag_) {
    case '<':
    case lexer::tag::kLe:
    case lexer::tag::kGe:
    case '>': {
      std::unique_ptr<lexer::Token> token = std::move(look_);
      Move();
      return std::make_unique<inter::Rel>(std::move(token), std::move(x),
                                          Expr());
    }
    default:
      return x;
  }
}

std::unique_ptr<inter::Expr> Parser::Expr() {
  std::unique_ptr<inter::Expr> x = Term();
  while (look_->tag_ == '+' || look_->tag_ == '-') {
    std::unique_ptr<lexer::Token> token = std::move(look_);
    Move();
    x = std::make_unique<inter::Arith>(std::move(token), std::move(x), Term());
  }
  return x;
}

std::unique_ptr<inter::Expr> Parser::Term() {
  std::unique_ptr<inter::Expr> x = Unary();
  while (look_->tag_ == '*' || look_->tag_ == '/') {
    std::unique_ptr<lexer::Token> token = std::move(look_);
    Move();
    x = std::make_unique<inter::Arith>(std::move(token), std::move(x), Unary());
  }
  return x;
}

std::unique_ptr<inter::Expr> Parser::Unary() {
  if (look_->tag_ == '-') {
    Move();
    return std::make_unique<inter::Unary>(lexer::Word::Minus().Clone(),
                                          Unary());
  } else if (look_->tag_ == '!') {
    std::unique_ptr<lexer::Token> token = std::move(look_);
    Move();
    return std::make_unique<inter::Not>(std::move(token), Unary());
  } else {
    return Factor();
  }
}

std::unique_ptr<inter::Expr> Parser::Factor() {
  std::unique_ptr<inter::Expr> x = nullptr;
  switch (look_->tag_) {
    case '(': {
      Move();
      x = Bool();
      Match(')');
      return x;
    }
    case lexer::tag::kNum: {
      x = std::make_unique<inter::Constant>(std::move(look_),
                                            symbols::Type::Int().CloneType());
      Move();
      return x;
    }
    case lexer::tag::kReal: {
      x = std::make_unique<inter::Constant>(std::move(look_),
                                            symbols::Type::Float().CloneType());
      Move();
      return x;
    }
    case lexer::tag::kTrue: {
      x = inter::Constant::True().Clone();
      Move();
      return x;
    }
    case lexer::tag::kFalse: {
      x = inter::Constant::False().Clone();
      Move();
      return x;
    }
    case lexer::tag::kId: {
      const inter::Id* id =
          top_->Get(*(static_cast<lexer::Word*>(look_.get())));
      if (id == nullptr) {
        Error(look_->ToString() + " undeclared!");
      }
      Move();
      if (look_->tag_ != '[') {
        return std::make_unique<inter::Id>(*id);
      }
      return Offset(id);
    }
    default: {
      Error("Syntax error!");
      return x;
    }
  }
}

std::unique_ptr<inter::Access> Parser::Offset(const inter::Id* a) {
  std::unique_ptr<inter::Expr> i, w, t1, t2, loc;
  std::unique_ptr<symbols::Type> type = a->type_->CloneType();
  Match('[');
  i = Bool();
  Match(']');
  type = static_cast_unique_ptr<symbols::Array>(type->CloneType())
             ->of_->CloneType();
  w = std::make_unique<inter::Constant>(type->width_);
  t1 = std::make_unique<inter::Arith>(std::make_unique<lexer::Token>('*'),
                                      std::move(i), std::move(w));
  loc = std::move(t1);
  while (look_->tag_ == '[') {
    Match('[');
    i = Bool();
    Match(']');
    type = static_cast_unique_ptr<symbols::Array>(type->CloneType())
               ->of_->CloneType();
    w = std::make_unique<inter::Constant>(type->width_);
    t1 = std::make_unique<inter::Arith>(std::make_unique<lexer::Token>('*'),
                                        std::move(i), std::move(w));
    t2 = std::make_unique<inter::Arith>(std::make_unique<lexer::Token>('+'),
                                        std::move(loc), std::move(t1));
    loc = std::move(t2);
  }
  return std::make_unique<inter::Access>(std::make_unique<inter::Id>(*a),
                                         std::move(loc), std::move(type));
}

}  // namespace parser
}  // namespace intellgraph
