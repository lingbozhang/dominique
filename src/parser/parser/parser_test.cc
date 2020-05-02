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

#include "gtest/gtest.h"
#include "src/lexer/token.h"
#include "src/parser/expr/constant.h"
#include "src/parser/expr/expr.h"
#include "src/symbol/array.h"
#include "src/symbol/type.h"
#include "src/util.h"

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

TEST_F(ParserTest, FactorConstantNum) {
  std::string codes = "123";
  lexer::Num expected_num = lexer::Num(123);
  inter::Constant expected_constant =
      inter::Constant(expected_num.Clone(), symbols::Type::Int().CloneType());

  parser_->ReadCodes(codes);
  std::unique_ptr<inter::Constant> constant =
      static_cast_unique_ptr<inter::Constant>(parser_->Factor());

  ASSERT_EQ(expected_constant, *constant);
}

TEST_F(ParserTest, FactorConstantReal) {
  std::string codes = "123.123";
  lexer::Real expected_real = lexer::Real(123.123);
  inter::Constant expected_constant = inter::Constant(
      expected_real.Clone(), symbols::Type::Float().CloneType());

  parser_->ReadCodes(codes);
  std::unique_ptr<inter::Constant> constant =
      static_cast_unique_ptr<inter::Constant>(parser_->Factor());

  ASSERT_EQ(expected_constant, *constant);
}

TEST_F(ParserTest, FactorConstantTrue) {
  std::string codes = "true";
  inter::Constant expected_constant = inter::Constant(
      lexer::Word::True().Clone(), symbols::Type::Bool().CloneType());

  parser_->ReadCodes(codes);
  std::unique_ptr<inter::Constant> constant =
      static_cast_unique_ptr<inter::Constant>(parser_->Factor());

  ASSERT_EQ(expected_constant, *constant);
}

TEST_F(ParserTest, FactorConstantFalse) {
  std::string codes = "false";
  inter::Constant expected_constant = inter::Constant(
      lexer::Word::False().Clone(), symbols::Type::Bool().CloneType());

  parser_->ReadCodes(codes);
  std::unique_ptr<inter::Constant> constant =
      static_cast_unique_ptr<inter::Constant>(parser_->Factor());

  ASSERT_EQ(expected_constant, *constant);
}

}  // namespace parser
}  // namespace intellgraph
