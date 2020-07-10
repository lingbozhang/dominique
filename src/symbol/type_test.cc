/* Copyright 2020 The IntellGraph Authors. All Rights Reserved.
Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at
   http://www.apache.org/licenses/LICENSE-2.0
Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

Contributor(s):
        Lingbo Zhang <lingboz2015@gmail.com>
==============================================================================*/
#include "src/symbol/type.h"

#include "src/lexer/tag.h"
#include "src/lexer/token.h"
#include "gtest/gtest.h"

namespace intellgraph {
namespace symbols {

TEST(TypeTest, Float) {
  EXPECT_EQ(Type::Float().tag_, lexer::tag::kBasic);
  EXPECT_EQ(Type::Float().id_, Type::TypeId::kFloat);
  EXPECT_EQ(Type::Float().width_, 8);
}

TEST(TypeTest, Int) {
  EXPECT_EQ(Type::Int().tag_, lexer::tag::kBasic);
  EXPECT_EQ(Type::Int().id_, Type::TypeId::kInt);
  EXPECT_EQ(Type::Int().width_, 4);
}

TEST(TypeTest, Char) {
  EXPECT_EQ(Type::Char().tag_, lexer::tag::kBasic);
  EXPECT_EQ(Type::Char().id_, Type::TypeId::kChar);
  EXPECT_EQ(Type::Char().width_, 1);
}

TEST(TypeTest, Bool) {
  EXPECT_EQ(Type::Bool().tag_, lexer::tag::kBasic);
  EXPECT_EQ(Type::Bool().id_, Type::TypeId::kBool);
  EXPECT_EQ(Type::Bool().width_, 1);
}

TEST(TypeTest, Null) {
  EXPECT_EQ(Type::Null().tag_, lexer::tag::kBasic);
  EXPECT_EQ(Type::Null().id_, Type::TypeId::kNull);
  EXPECT_EQ(Type::Null().width_, 0);
}

TEST(TypeTest, IsNumeric) {
  EXPECT_EQ(Type::IsNumeric(Type::Float()), true);
  EXPECT_EQ(Type::IsNumeric(Type::Float()), true);
  EXPECT_EQ(Type::IsNumeric(Type::Char()), true);
  EXPECT_EQ(Type::IsNumeric(Type::Bool()), false);
  EXPECT_EQ(Type::IsNumeric(Type::Null()), false);
}

TEST(TypeTest, Max) {
  EXPECT_EQ(Type::Max(Type::Float(), Type::Float()), Type::Float());
  EXPECT_EQ(Type::Max(Type::Float(), Type::Int()), Type::Float());
  EXPECT_EQ(Type::Max(Type::Float(), Type::Char()), Type::Float());
  EXPECT_EQ(Type::Max(Type::Float(), Type::Bool()), Type::Null());
  EXPECT_EQ(Type::Max(Type::Float(), Type::Null()), Type::Null());
  EXPECT_EQ(Type::Max(Type::Int(), Type::Int()), Type::Int());
  EXPECT_EQ(Type::Max(Type::Int(), Type::Char()), Type::Int());
  EXPECT_EQ(Type::Max(Type::Int(), Type::Bool()), Type::Null());
  EXPECT_EQ(Type::Max(Type::Int(), Type::Null()), Type::Null());
  EXPECT_EQ(Type::Max(Type::Char(), Type::Char()), Type::Char());
  EXPECT_EQ(Type::Max(Type::Char(), Type::Bool()), Type::Null());
  EXPECT_EQ(Type::Max(Type::Char(), Type::Null()), Type::Null());
}

}  // namespace symbols
}  // namespace intellgraph
