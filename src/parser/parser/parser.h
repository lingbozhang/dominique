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
#ifndef INTELLGRAPH_SRC_PARSER_PARSER_PARSER_H_
#define INTELLGRAPH_SRC_PARSER_PARSER_PARSER_H_

#include "src/lexer/lexer.h"
#include "src/lexer/token.h"
#include "src/parser/expr/access.h"
#include "src/parser/expr/expr.h"
#include "src/parser/expr/id.h"
#include "src/parser/stmt/stmt.h"
#include "src/symbol/env.h"
#include "src/symbol/type.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "gtest/gtest_prod.h"

namespace intellgraph {
namespace parser {

class Parser {
public:
  Parser(std::unique_ptr<lexer::Lexer> lex);
  ~Parser();

  void ReadCodes(const std::string &codes);
  void Program();

  std::unique_ptr<inter::Stmt> Block();
  std::unique_ptr<symbols::Type> Type();
  std::unique_ptr<inter::Stmt> Stmts();
  std::unique_ptr<inter::Stmt> Stmt();
  std::unique_ptr<inter::Stmt> Assign();
  std::unique_ptr<inter::Expr> Bool();
  std::unique_ptr<inter::Expr> Join();
  std::unique_ptr<inter::Expr> Equality();
  std::unique_ptr<inter::Expr> Rel();
  std::unique_ptr<inter::Expr> Expr();
  std::unique_ptr<inter::Expr> Term();
  std::unique_ptr<inter::Expr> Unary();
  std::unique_ptr<inter::Expr> Factor();

private:

  void Move();
  void Error(const std::string &str);
  void Match(int t);

  FRIEND_TEST(ParserTest, DimsOne);
  FRIEND_TEST(ParserTest, DimsTwo);
  FRIEND_TEST(ParserTest, DeclsBool);
  FRIEND_TEST(ParserTest, DeclsBoolArray);
  FRIEND_TEST(ParserTest, DeclsInt);
  FRIEND_TEST(ParserTest, DeclsIntArray);
  FRIEND_TEST(ParserTest, DeclsFloat);
  FRIEND_TEST(ParserTest, DeclsFloatArray);
  FRIEND_TEST(ParserTest, DeclsChar);
  FRIEND_TEST(ParserTest, DeclsCharArray);
  FRIEND_TEST(ParserTest, AssignBool);
  FRIEND_TEST(ParserTest, AssignBoolArray);
  FRIEND_TEST(ParserTest, AssignInt);
  FRIEND_TEST(ParserTest, AssignIntArray);
  FRIEND_TEST(ParserTest, AssignFloat);
  FRIEND_TEST(ParserTest, AssignFloatArray);

  void Decls();
  std::unique_ptr<symbols::Type> Dims(std::unique_ptr<symbols::Type> p);
  std::unique_ptr<inter::Access> Offset(const inter::Id *a);

  std::unique_ptr<llvm::LLVMContext> llvm_context_;
  std::unique_ptr<llvm::IRBuilder<>> llvm_builder_;
  std::unique_ptr<llvm::Module> llvm_module_;

  std::unique_ptr<lexer::Lexer> lex_;
  std::unique_ptr<lexer::Token> look_;
  std::unique_ptr<symbols::Env> top_;
  int used_ = 0;
};

} // namespace parser
} // namespace intellgraph

#endif  // INTELLGRAPH_SRC_PARSER_PARSER_PARSER_H_
