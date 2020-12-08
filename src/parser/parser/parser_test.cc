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

#include <memory>

#include "src/lexer/token.h"
#include "src/parser/expr/access.h"
#include "src/parser/expr/and.h"
#include "src/parser/expr/arith.h"
#include "src/parser/expr/constant.h"
#include "src/parser/expr/expr.h"
#include "src/parser/expr/id.h"
#include "src/parser/expr/not.h"
#include "src/parser/expr/rel.h"
#include "src/parser/expr/unary.h"
#include "src/parser/stmt/set.h"
#include "src/parser/stmt/set_elem.h"
#include "src/symbol/array.h"
#include "src/symbol/type.h"
#include "src/util.h"
#include "gtest/gtest.h"

namespace intellgraph {
namespace parser {

class ParserTest : public testing::Test {
 protected:
  ParserTest() {
    auto lex = std::make_unique<lexer::Lexer>();
    parser_ = std::make_unique<Parser>(std::move(lex));
  }
  ~ParserTest() override = default;

  std::unique_ptr<Parser> parser_;
};

TEST_F(ParserTest, DimsOne) {
  std::string codes = "[1]";
  symbols::Type int_type = symbols::Type::Int();
  symbols::Array expected_array = symbols::Array(int_type.CloneType(), 1);

  parser_->ReadCodes(codes);
  std::unique_ptr<symbols::Array> array =
      static_cast_unique_ptr<symbols::Array>(
          parser_->Dims(int_type.CloneType()));

  ASSERT_EQ(expected_array, *array);
}

TEST_F(ParserTest, DimsTwo) {
  std::string codes = "[1][2]";
  symbols::Type int_type = symbols::Type::Int();
  symbols::Array expected_array = symbols::Array(
      std::make_unique<symbols::Array>(int_type.CloneType(), 2), 1);

  parser_->ReadCodes(codes);
  std::unique_ptr<symbols::Array> array =
      static_cast_unique_ptr<symbols::Array>(
          parser_->Dims(int_type.CloneType()));

  ASSERT_EQ(expected_array, *array);
}

TEST_F(ParserTest, TypeInt) {
  std::string codes = "int";
  symbols::Type expected_type = symbols::Type::Int();

  parser_->ReadCodes(codes);
  std::unique_ptr<symbols::Type> type = parser_->Type();

  ASSERT_EQ(expected_type, *type);
}

TEST_F(ParserTest, TypeIntArray) {
  std::string codes = "int[1]";
  symbols::Array expected_array =
      symbols::Array(symbols::Type::Int().CloneType(), 1);

  parser_->ReadCodes(codes);
  std::unique_ptr<symbols::Array> array =
      static_cast_unique_ptr<symbols::Array>(parser_->Type());

  ASSERT_EQ(expected_array, *array);
}

TEST_F(ParserTest, TypeFloat) {
  std::string codes = "float";
  symbols::Type expected_type = symbols::Type::Float();

  parser_->ReadCodes(codes);
  std::unique_ptr<symbols::Type> type = parser_->Type();

  ASSERT_EQ(expected_type, *type);
}

TEST_F(ParserTest, TypeFloatArray) {
  std::string codes = "float[1]";
  symbols::Array expected_array =
      symbols::Array(symbols::Type::Float().CloneType(), 1);

  parser_->ReadCodes(codes);
  std::unique_ptr<symbols::Array> array =
      static_cast_unique_ptr<symbols::Array>(parser_->Type());

  ASSERT_EQ(expected_array, *array);
}

TEST_F(ParserTest, TypeChar) {
  std::string codes = "char";
  symbols::Type expected_type = symbols::Type::Char();

  parser_->ReadCodes(codes);
  std::unique_ptr<symbols::Type> type = parser_->Type();

  ASSERT_EQ(expected_type, *type);
}

TEST_F(ParserTest, TypeCharArray) {
  std::string codes = "char[1]";
  symbols::Array expected_array =
      symbols::Array(symbols::Type::Char().CloneType(), 1);

  parser_->ReadCodes(codes);
  std::unique_ptr<symbols::Array> array =
      static_cast_unique_ptr<symbols::Array>(parser_->Type());

  ASSERT_EQ(expected_array, *array);
}

TEST_F(ParserTest, TypeBool) {
  std::string codes = "bool";
  symbols::Type expected_type = symbols::Type::Bool();

  parser_->ReadCodes(codes);
  std::unique_ptr<symbols::Type> type = parser_->Type();

  ASSERT_EQ(expected_type, *type);
}

TEST_F(ParserTest, TypeBoolArray) {
  std::string codes = "bool[1]";
  symbols::Array expected_array =
      symbols::Array(symbols::Type::Bool().CloneType(), 1);

  parser_->ReadCodes(codes);
  std::unique_ptr<symbols::Array> array =
      static_cast_unique_ptr<symbols::Array>(parser_->Type());

  ASSERT_EQ(expected_array, *array);
}

TEST_F(ParserTest, DeclsBool) {
  std::string codes = "bool id;";
  std::unique_ptr<symbols::Type> expected_type =
      symbols::Type::Bool().CloneType();
  lexer::Word expected_word = lexer::Word("id", lexer::tag::kId);
  int offset = 0;
  inter::Id expected_id =
      inter::Id(std::make_unique<lexer::Word>(expected_word),
                std::move(expected_type), offset);

  parser_->ReadCodes(codes);
  parser_->Decls();
  inter::Id* id = parser_->top_->Get(expected_word);

  ASSERT_EQ(expected_id, *id);
}

TEST_F(ParserTest, DeclsBoolArray) {
  std::string codes = "bool[10] id;";
  std::unique_ptr<symbols::Type> expected_type =
      std::make_unique<symbols::Array>(symbols::Type::Bool().CloneType(), 10);
  lexer::Word expected_word = lexer::Word("id", lexer::tag::kId);
  int offset = 0;
  inter::Id expected_id =
      inter::Id(std::make_unique<lexer::Word>(expected_word),
                std::move(expected_type), offset);

  parser_->ReadCodes(codes);
  parser_->Decls();
  inter::Id *id = parser_->top_->Get(expected_word);

  ASSERT_EQ(expected_id, *id);
}

TEST_F(ParserTest, DeclsInt) {
  std::string codes = "int id;";
  std::unique_ptr<symbols::Type> expected_type =
      symbols::Type::Int().CloneType();
  lexer::Word expected_word = lexer::Word("id", lexer::tag::kId);
  int offset = 0;
  inter::Id expected_id =
      inter::Id(std::make_unique<lexer::Word>(expected_word),
                std::move(expected_type), offset);

  parser_->ReadCodes(codes);
  parser_->Decls();
  inter::Id *id = parser_->top_->Get(expected_word);

  ASSERT_EQ(expected_id, *id);
}

TEST_F(ParserTest, DeclsIntArray) {
  std::string codes = "int[10] id;";
  std::unique_ptr<symbols::Type> expected_type =
      std::make_unique<symbols::Array>(symbols::Type::Int().CloneType(), 10);
  lexer::Word expected_word = lexer::Word("id", lexer::tag::kId);
  int offset = 0;
  inter::Id expected_id =
      inter::Id(std::make_unique<lexer::Word>(expected_word),
                std::move(expected_type), offset);

  parser_->ReadCodes(codes);
  parser_->Decls();
  inter::Id *id = parser_->top_->Get(expected_word);

  ASSERT_EQ(expected_id, *id);
}

TEST_F(ParserTest, DeclsFloat) {
  std::string codes = "float id;";
  std::unique_ptr<symbols::Type> expected_type =
      symbols::Type::Float().CloneType();
  lexer::Word expected_word = lexer::Word("id", lexer::tag::kId);
  int offset = 0;
  inter::Id expected_id =
      inter::Id(std::make_unique<lexer::Word>(expected_word),
                std::move(expected_type), offset);

  parser_->ReadCodes(codes);
  parser_->Decls();
  inter::Id *id = parser_->top_->Get(expected_word);

  ASSERT_EQ(expected_id, *id);
}

TEST_F(ParserTest, DeclsFloatArray) {
  std::string codes = "float[10] id;";
  std::unique_ptr<symbols::Type> expected_type =
      std::make_unique<symbols::Array>(symbols::Type::Float().CloneType(), 10);
  lexer::Word expected_word = lexer::Word("id", lexer::tag::kId);
  int offset = 0;
  inter::Id expected_id =
      inter::Id(std::make_unique<lexer::Word>(expected_word),
                std::move(expected_type), offset);

  parser_->ReadCodes(codes);
  parser_->Decls();
  inter::Id *id = parser_->top_->Get(expected_word);

  ASSERT_EQ(expected_id, *id);
}

TEST_F(ParserTest, DeclsChar) {
  std::string codes = "char id;";
  std::unique_ptr<symbols::Type> expected_type =
      symbols::Type::Char().CloneType();
  lexer::Word expected_word = lexer::Word("id", lexer::tag::kId);
  int offset = 0;
  inter::Id expected_id =
      inter::Id(std::make_unique<lexer::Word>(expected_word),
                std::move(expected_type), offset);

  parser_->ReadCodes(codes);
  parser_->Decls();
  inter::Id *id = parser_->top_->Get(expected_word);

  ASSERT_EQ(expected_id, *id);
}

TEST_F(ParserTest, DeclsCharArray) {
  std::string codes = "char[10] id;";
  std::unique_ptr<symbols::Type> expected_type =
      std::make_unique<symbols::Array>(symbols::Type::Char().CloneType(), 10);
  lexer::Word expected_word = lexer::Word("id", lexer::tag::kId);
  int offset = 0;
  inter::Id expected_id =
      inter::Id(std::make_unique<lexer::Word>(expected_word),
                std::move(expected_type), offset);

  parser_->ReadCodes(codes);
  parser_->Decls();
  inter::Id *id = parser_->top_->Get(expected_word);

  ASSERT_EQ(expected_id, *id);
}

TEST_F(ParserTest, FactorConstantNum) {
  std::string codes = "123";
  inter::Constant expected_constant = inter::Constant(
      lexer::Num(123).Clone(), symbols::Type::Int().CloneType());

  parser_->ReadCodes(codes);
  std::unique_ptr<inter::Constant> constant =
      static_cast_unique_ptr<inter::Constant>(parser_->Factor());

  ASSERT_EQ(expected_constant, *constant);
}

TEST_F(ParserTest, FactorConstantParenthesis) {
  std::string codes = "(123)";
  inter::Constant expected_constant = inter::Constant(
      lexer::Num(123).Clone(), symbols::Type::Int().CloneType());

  parser_->ReadCodes(codes);
  std::unique_ptr<inter::Constant> constant =
      static_cast_unique_ptr<inter::Constant>(parser_->Factor());

  ASSERT_EQ(expected_constant, *constant);
}

TEST_F(ParserTest, FactorConstantReal) {
  std::string codes = "123.123";
  inter::Constant expected_constant = inter::Constant(
      lexer::Real(123.123).Clone(), symbols::Type::Float().CloneType());

  parser_->ReadCodes(codes);
  std::unique_ptr<inter::Constant> constant =
      static_cast_unique_ptr<inter::Constant>(parser_->Factor());

  ASSERT_EQ(expected_constant, *constant);
}

TEST_F(ParserTest, FactorConstantTrue) {
  std::string codes = "true";
  inter::Constant expected_constant = inter::Constant::True();

  parser_->ReadCodes(codes);
  std::unique_ptr<inter::Constant> constant =
      static_cast_unique_ptr<inter::Constant>(parser_->Factor());

  ASSERT_EQ(expected_constant, *constant);
}

TEST_F(ParserTest, FactorConstantFalse) {
  std::string codes = "false";
  inter::Constant expected_constant = inter::Constant::False();

  parser_->ReadCodes(codes);
  std::unique_ptr<inter::Constant> constant =
      static_cast_unique_ptr<inter::Constant>(parser_->Factor());

  ASSERT_EQ(expected_constant, *constant);
}

TEST_F(ParserTest, UnaryConstantNum) {
  std::string codes = "-123";
  inter::Constant expected_constant = inter::Constant(
      std::make_unique<lexer::Num>(123), symbols::Type::Int().CloneType());
  inter::Unary expected_unary =
      inter::Unary(lexer::Word::Minus().Clone(), expected_constant.Clone());

  parser_->ReadCodes(codes);
  std::unique_ptr<inter::Unary> unary =
      static_cast_unique_ptr<inter::Unary>(parser_->Unary());

  ASSERT_EQ(expected_unary, *unary);
}

TEST_F(ParserTest, UnaryConstantReal) {
  std::string codes = "-123.123";
  inter::Constant expected_constant =
      inter::Constant(std::make_unique<lexer::Real>(123.123),
                      symbols::Type::Float().CloneType());
  inter::Unary expected_unary =
      inter::Unary(lexer::Word::Minus().Clone(), expected_constant.Clone());

  parser_->ReadCodes(codes);
  std::unique_ptr<inter::Unary> unary =
      static_cast_unique_ptr<inter::Unary>(parser_->Unary());

  ASSERT_EQ(expected_unary, *unary);
}

TEST_F(ParserTest, UnaryNot) {
  std::string codes = "!true";
  inter::Not expected_not =
      inter::Not(lexer::Token('!').Clone(), inter::Constant::True().Clone());

  parser_->ReadCodes(codes);
  std::unique_ptr<inter::Not> expr_not =
      static_cast_unique_ptr<inter::Not>(parser_->Unary());

  ASSERT_EQ(expected_not, *expr_not);
}

TEST_F(ParserTest, TermMultipleOne) {
  std::string codes = "123 * 123";
  inter::Constant x = inter::Constant(lexer::Num(123).Clone(),
                                      symbols::Type::Int().CloneType());
  inter::Arith expected_arith =
      inter::Arith(lexer::Token('*').Clone(), x.Clone(), x.Clone());

  parser_->ReadCodes(codes);
  std::unique_ptr<inter::Arith> arith =
      static_cast_unique_ptr<inter::Arith>(parser_->Term());

  ASSERT_EQ(expected_arith, *arith);
}

TEST_F(ParserTest, TermMultipleTwo) {
  std::string codes = "123 * 123 * 123.123";
  inter::Constant x1 = inter::Constant(lexer::Num(123).Clone(),
                                       symbols::Type::Int().CloneType());
  inter::Constant x2 = inter::Constant(lexer::Real(123.123).Clone(),
                                       symbols::Type::Float().CloneType());
  inter::Arith expected_mult_one =
      inter::Arith(lexer::Token('*').Clone(), x1.Clone(), x1.Clone());
  inter::Arith expected_mult_two = inter::Arith(
      lexer::Token('*').Clone(), expected_mult_one.Clone(), x2.Clone());

  parser_->ReadCodes(codes);
  std::unique_ptr<inter::Arith> arith =
      static_cast_unique_ptr<inter::Arith>(parser_->Term());

  ASSERT_EQ(expected_mult_two, *arith);
}

TEST_F(ParserTest, TermDivideOne) {
  std::string codes = "123 / 123";
  inter::Constant x = inter::Constant(lexer::Num(123).Clone(),
                                      symbols::Type::Int().CloneType());
  inter::Arith expected_arith =
      inter::Arith(lexer::Token('/').Clone(), x.Clone(), x.Clone());

  parser_->ReadCodes(codes);
  std::unique_ptr<inter::Arith> arith =
      static_cast_unique_ptr<inter::Arith>(parser_->Term());

  ASSERT_EQ(expected_arith, *arith);
}

TEST_F(ParserTest, TermDivideTwo) {
  std::string codes = "123 / 123 / -123.123";
  inter::Constant x1 = inter::Constant(lexer::Num(123).Clone(),
                                       symbols::Type::Int().CloneType());
  inter::Constant expected_constant =
      inter::Constant(std::make_unique<lexer::Real>(123.123),
                      symbols::Type::Float().CloneType());
  inter::Unary x2 =
      inter::Unary(lexer::Word::Minus().Clone(), expected_constant.Clone());
  inter::Arith expected_div_one =
      inter::Arith(lexer::Token('/').Clone(), x1.Clone(), x1.Clone());
  inter::Arith expected_div_two = inter::Arith(
      lexer::Token('/').Clone(), expected_div_one.Clone(), x2.Clone());

  parser_->ReadCodes(codes);
  std::unique_ptr<inter::Arith> arith =
      static_cast_unique_ptr<inter::Arith>(parser_->Term());

  ASSERT_EQ(expected_div_two, *arith);
}

TEST_F(ParserTest, TermDivisionAndMultiplication) {
  std::string codes = "123 / 123 * -123.123";
  inter::Constant x1 = inter::Constant(lexer::Num(123).Clone(),
                                       symbols::Type::Int().CloneType());
  inter::Constant expected_constant =
      inter::Constant(std::make_unique<lexer::Real>(123.123),
                      symbols::Type::Float().CloneType());
  inter::Unary x2 =
      inter::Unary(lexer::Word::Minus().Clone(), expected_constant.Clone());
  inter::Arith expected_div_one =
      inter::Arith(lexer::Token('/').Clone(), x1.Clone(), x1.Clone());
  inter::Arith expected_div_two = inter::Arith(
      lexer::Token('*').Clone(), expected_div_one.Clone(), x2.Clone());

  parser_->ReadCodes(codes);
  std::unique_ptr<inter::Arith> arith =
      static_cast_unique_ptr<inter::Arith>(parser_->Term());

  ASSERT_EQ(expected_div_two, *arith);
}

TEST_F(ParserTest, ExprAddOne) {
  std::string codes = "123 + 123.123";
  inter::Constant x1 = inter::Constant(lexer::Num(123).Clone(),
                                       symbols::Type::Int().CloneType());
  inter::Constant x2 = inter::Constant(lexer::Real(123.123).Clone(),
                                       symbols::Type::Float().CloneType());
  inter::Arith expected_arith =
      inter::Arith(lexer::Token('+').Clone(), x1.Clone(), x2.Clone());

  parser_->ReadCodes(codes);
  std::unique_ptr<inter::Arith> arith =
      static_cast_unique_ptr<inter::Arith>(parser_->Expr());

  ASSERT_EQ(expected_arith, *arith);
}

TEST_F(ParserTest, ExprAddTwo) {
  std::string codes = "123 + 123.123 + 123";
  inter::Constant x1 = inter::Constant(lexer::Num(123).Clone(),
                                       symbols::Type::Int().CloneType());
  inter::Constant x2 = inter::Constant(lexer::Real(123.123).Clone(),
                                       symbols::Type::Float().CloneType());
  inter::Arith expected_add_one =
      inter::Arith(lexer::Token('+').Clone(), x1.Clone(), x2.Clone());
  inter::Arith expected_add_two = inter::Arith(
      lexer::Token('+').Clone(), expected_add_one.Clone(), x1.Clone());

  parser_->ReadCodes(codes);
  std::unique_ptr<inter::Arith> arith =
      static_cast_unique_ptr<inter::Arith>(parser_->Expr());

  ASSERT_EQ(expected_add_two, *arith);
}

TEST_F(ParserTest, ExprMinusOne) {
  std::string codes = "123 - 123.123";
  inter::Constant x1 = inter::Constant(lexer::Num(123).Clone(),
                                       symbols::Type::Int().CloneType());
  inter::Constant x2 = inter::Constant(lexer::Real(123.123).Clone(),
                                       symbols::Type::Float().CloneType());
  inter::Arith expected_arith =
      inter::Arith(lexer::Token('-').Clone(), x1.Clone(), x2.Clone());

  parser_->ReadCodes(codes);
  std::unique_ptr<inter::Arith> arith =
      static_cast_unique_ptr<inter::Arith>(parser_->Expr());

  ASSERT_EQ(expected_arith, *arith);
}

TEST_F(ParserTest, ExprMinusTwo) {
  std::string codes = "123 - 123.123 - 123";
  inter::Constant x1 = inter::Constant(lexer::Num(123).Clone(),
                                       symbols::Type::Int().CloneType());
  inter::Constant x2 = inter::Constant(lexer::Real(123.123).Clone(),
                                       symbols::Type::Float().CloneType());
  inter::Arith expected_minus_one =
      inter::Arith(lexer::Token('-').Clone(), x1.Clone(), x2.Clone());
  inter::Arith expected_minus_two = inter::Arith(
      lexer::Token('-').Clone(), expected_minus_one.Clone(), x1.Clone());

  parser_->ReadCodes(codes);
  std::unique_ptr<inter::Arith> arith =
      static_cast_unique_ptr<inter::Arith>(parser_->Expr());

  ASSERT_EQ(expected_minus_two, *arith);
}

TEST_F(ParserTest, RelLT) {
  std::string codes = "123 < 123";
  inter::Constant x1 = inter::Constant(lexer::Num(123).Clone(),
                                       symbols::Type::Int().CloneType());
  inter::Rel expected_rel =
      inter::Rel(lexer::Token('<').Clone(), x1.Clone(), x1.Clone());

  parser_->ReadCodes(codes);
  std::unique_ptr<inter::Rel> arith =
      static_cast_unique_ptr<inter::Rel>(parser_->Rel());

  ASSERT_EQ(expected_rel, *arith);
}

TEST_F(ParserTest, RelLE) {
  std::string codes = "123 <= 123";
  inter::Constant x1 = inter::Constant(lexer::Num(123).Clone(),
                                       symbols::Type::Int().CloneType());
  inter::Rel expected_rel =
      inter::Rel(lexer::Token(lexer::tag::kLe).Clone(), x1.Clone(), x1.Clone());

  parser_->ReadCodes(codes);
  std::unique_ptr<inter::Rel> arith =
      static_cast_unique_ptr<inter::Rel>(parser_->Rel());

  ASSERT_EQ(expected_rel, *arith);
}

TEST_F(ParserTest, RelGT) {
  std::string codes = "123 > 123";
  inter::Constant x1 = inter::Constant(lexer::Num(123).Clone(),
                                       symbols::Type::Int().CloneType());
  inter::Rel expected_rel =
      inter::Rel(lexer::Token('>').Clone(), x1.Clone(), x1.Clone());

  parser_->ReadCodes(codes);
  std::unique_ptr<inter::Rel> arith =
      static_cast_unique_ptr<inter::Rel>(parser_->Rel());

  ASSERT_EQ(expected_rel, *arith);
}

TEST_F(ParserTest, RelGE) {
  std::string codes = "123 >= 123";
  inter::Constant x1 = inter::Constant(lexer::Num(123).Clone(),
                                       symbols::Type::Int().CloneType());
  inter::Rel expected_rel =
      inter::Rel(lexer::Token(lexer::tag::kGe).Clone(), x1.Clone(), x1.Clone());

  parser_->ReadCodes(codes);
  std::unique_ptr<inter::Rel> arith =
      static_cast_unique_ptr<inter::Rel>(parser_->Rel());

  ASSERT_EQ(expected_rel, *arith);
}

TEST_F(ParserTest, EqualityEq) {
  std::string codes = "123 >= 123 == 123 < 123";
  inter::Constant x1 = inter::Constant(lexer::Num(123).Clone(),
                                       symbols::Type::Int().CloneType());
  inter::Rel rel1 =
      inter::Rel(lexer::Token(lexer::tag::kGe).Clone(), x1.Clone(), x1.Clone());
  inter::Rel rel2 =
      inter::Rel(lexer::Token('<').Clone(), x1.Clone(), x1.Clone());
  inter::Rel expected_rel = inter::Rel(lexer::Token(lexer::tag::kEq).Clone(),
                                       rel1.Clone(), rel2.Clone());

  //  parser_->ReadCodes(codes);
  //  std::unique_ptr<inter::Rel> arith =
  //      static_cast_unique_ptr<inter::Rel>(parser_->Equality());
  //
  //  ASSERT_EQ(expected_rel, *arith);
}

TEST_F(ParserTest, EqualityNe) {
  std::string codes = "123 >= 123 != 123 < 123";
  inter::Constant x1 = inter::Constant(lexer::Num(123).Clone(),
                                       symbols::Type::Int().CloneType());
  inter::Rel rel1 =
      inter::Rel(lexer::Token(lexer::tag::kGe).Clone(), x1.Clone(), x1.Clone());
  inter::Rel rel2 =
      inter::Rel(lexer::Token('<').Clone(), x1.Clone(), x1.Clone());
  inter::Rel expected_rel = inter::Rel(lexer::Token(lexer::tag::kNe).Clone(),
                                       rel1.Clone(), rel2.Clone());

  parser_->ReadCodes(codes);
  std::unique_ptr<inter::Rel> arith =
      static_cast_unique_ptr<inter::Rel>(parser_->Equality());

  ASSERT_EQ(expected_rel, *arith);
}

TEST_F(ParserTest, JoinAnd) {
  std::string codes = "123 >= 123 && 123 < 123";
  inter::Constant x1 = inter::Constant(lexer::Num(123).Clone(),
                                       symbols::Type::Int().CloneType());
  inter::Rel rel1 =
      inter::Rel(lexer::Token(lexer::tag::kGe).Clone(), x1.Clone(), x1.Clone());
  inter::Rel rel2 =
      inter::Rel(lexer::Token('<').Clone(), x1.Clone(), x1.Clone());
  inter::And expected_and = inter::And(lexer::Token(lexer::tag::kAnd).Clone(),
                                       rel1.Clone(), rel2.Clone());

  parser_->ReadCodes(codes);
  std::unique_ptr<inter::Rel> arith =
      static_cast_unique_ptr<inter::Rel>(parser_->Join());

  ASSERT_EQ(expected_and, *arith);
}

TEST_F(ParserTest, BoolOr) {
  std::string codes = "(123 >= 123) || (123 < 123)";
  inter::Constant x1 = inter::Constant(lexer::Num(123).Clone(),
                                       symbols::Type::Int().CloneType());
  inter::Rel rel1 =
      inter::Rel(lexer::Token(lexer::tag::kGe).Clone(), x1.Clone(), x1.Clone());
  inter::Rel rel2 =
      inter::Rel(lexer::Token('<').Clone(), x1.Clone(), x1.Clone());
  inter::And expected_and = inter::And(lexer::Token(lexer::tag::kOr).Clone(),
                                       rel1.Clone(), rel2.Clone());

  parser_->ReadCodes(codes);
  std::unique_ptr<inter::Rel> arith =
      static_cast_unique_ptr<inter::Rel>(parser_->Bool());

  ASSERT_EQ(expected_and, *arith);
}

TEST_F(ParserTest, AssignBool) {
  std::string codes = "bool id; id = true;";
  inter::Id expected_id =
      inter::Id(std::make_unique<lexer::Word>("id", lexer::tag::kId),
                symbols::Type::Bool().CloneType(), 0 /* offset */);
  inter::Set expected_stmt =
      inter::Set(std::make_unique<inter::Id>(expected_id),
                 inter::Constant::True().Clone());

  parser_->ReadCodes(codes);
  parser_->Decls();
  std::unique_ptr<inter::Set> stmt =
      static_cast_unique_ptr<inter::Set>(parser_->Assign());

  ASSERT_EQ(expected_stmt, *stmt);
}

TEST_F(ParserTest, AssignBoolArray) {
  std::string codes = "bool[10] id; id[1] = false;";
  inter::Id expected_id =
      inter::Id(std::make_unique<lexer::Word>("id", lexer::tag::kId),
                std::make_unique<symbols::Array>(
                    symbols::Type::Bool().CloneType(), 10 /* array_size */),
                0 /* offset */);
  inter::Access expected_index = inter::Access(
      std::make_unique<inter::Id>(expected_id),
      std::make_unique<inter::Arith>(
          std::make_unique<lexer::Token>('*'), inter::Constant(1).Clone(),
          std::make_unique<inter::Constant>(1 /* bool_width */)),
      symbols::Type::Bool().CloneType());
  inter::SetElem expected_stmt =
      inter::SetElem(std::make_unique<inter::Access>(expected_index),
                     inter::Constant::False().Clone());

  parser_->ReadCodes(codes);
  parser_->Decls();
  std::unique_ptr<inter::SetElem> stmt =
      static_cast_unique_ptr<inter::SetElem>(parser_->Assign());

  ASSERT_EQ(expected_stmt, *stmt);
}

TEST_F(ParserTest, AssignInt) {
  std::string codes = "int id; id = 10;";
  inter::Id expected_id =
      inter::Id(std::make_unique<lexer::Word>("id", lexer::tag::kId),
                symbols::Type::Int().CloneType(), 0 /* offset */);
  inter::Set expected_stmt = inter::Set(
      std::make_unique<inter::Id>(expected_id), inter::Constant(10).Clone());

  parser_->ReadCodes(codes);
  parser_->Decls();
  std::unique_ptr<inter::Set> stmt =
      static_cast_unique_ptr<inter::Set>(parser_->Assign());

  ASSERT_EQ(expected_stmt, *stmt);
}

TEST_F(ParserTest, AssignIntArray) {
  std::string codes = "int[10] id; id[1] = 22;";
  inter::Id expected_id =
      inter::Id(std::make_unique<lexer::Word>("id", lexer::tag::kId),
                std::make_unique<symbols::Array>(
                    symbols::Type::Int().CloneType(), 10 /* array_size */),
                0 /* offset */);
  inter::Access expected_index = inter::Access(
      std::make_unique<inter::Id>(expected_id),
      std::make_unique<inter::Arith>(
          std::make_unique<lexer::Token>('*'), inter::Constant(1).Clone(),
          std::make_unique<inter::Constant>(4 /* int_width */)),
      symbols::Type::Int().CloneType());
  inter::SetElem expected_stmt =
      inter::SetElem(std::make_unique<inter::Access>(expected_index),
                     inter::Constant(22).Clone());

  parser_->ReadCodes(codes);
  parser_->Decls();
  std::unique_ptr<inter::SetElem> stmt =
      static_cast_unique_ptr<inter::SetElem>(parser_->Assign());

  ASSERT_EQ(expected_stmt, *stmt);
}

TEST_F(ParserTest, AssignFloat) {
  std::string codes = "float id; id = 10.4;";
  inter::Id expected_id =
      inter::Id(std::make_unique<lexer::Word>("id", lexer::tag::kId),
                symbols::Type::Float().CloneType(), 0 /* offset */);
  inter::Set expected_stmt = inter::Set(
      std::make_unique<inter::Id>(expected_id),
      std::make_unique<inter::Constant>(std::make_unique<lexer::Real>(10.4),
                                        symbols::Type::Float().CloneType()));

  parser_->ReadCodes(codes);
  parser_->Decls();
  std::unique_ptr<inter::Set> stmt =
      static_cast_unique_ptr<inter::Set>(parser_->Assign());

  ASSERT_EQ(expected_stmt, *stmt);
}

TEST_F(ParserTest, AssignFloatArray) {
  std::string codes = "float[20] id; id[1] = 88.88;";
  inter::Id expected_id =
      inter::Id(std::make_unique<lexer::Word>("id", lexer::tag::kId),
                std::make_unique<symbols::Array>(
                    symbols::Type::Float().CloneType(), 20 /* array_size */),
                0 /* offset */);
  inter::Access expected_index = inter::Access(
      std::make_unique<inter::Id>(expected_id),
      std::make_unique<inter::Arith>(
          std::make_unique<lexer::Token>('*'), inter::Constant(1).Clone(),
          std::make_unique<inter::Constant>(8 /* int_width */)),
      symbols::Type::Float().CloneType());
  inter::SetElem expected_stmt = inter::SetElem(
      std::make_unique<inter::Access>(expected_index),
      std::make_unique<inter::Constant>(std::make_unique<lexer::Real>(88.88),
                                        symbols::Type::Float().CloneType()));

  parser_->ReadCodes(codes);
  parser_->Decls();
  std::unique_ptr<inter::SetElem> stmt =
      static_cast_unique_ptr<inter::SetElem>(parser_->Assign());

  ASSERT_EQ(expected_stmt, *stmt);
}

}  // namespace parser
}  // namespace intellgraph
