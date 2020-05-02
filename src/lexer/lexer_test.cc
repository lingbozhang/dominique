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
#include "src/lexer/lexer.h"

#include "gtest/gtest.h"
#include "src/lexer/token.h"

namespace intellgraph {
namespace lexer {

TEST(LexerTest, EmptyString) {
  Lexer lex = Lexer();
  std::unique_ptr<Token> token = lex.Scan();
  EXPECT_EQ(token->tag_, (int)(' '));
}

TEST(LexerTest, True) {
  Lexer lex = Lexer();
  lex.ReadCodes("true");
  std::unique_ptr<Token> token = lex.Scan();

  EXPECT_EQ(token->tag_, tag::kTrue);
  EXPECT_EQ(static_cast<Word*>(token.get())->lexeme_, "true");
}

TEST(LexerTest, Integer) {
  Lexer lex = Lexer();
  lex.ReadCodes("0 123");
  std::unique_ptr<Token> token1 = lex.Scan();
  std::unique_ptr<Token> token2 = lex.Scan();

  EXPECT_EQ(token1->tag_, tag::kNum);
  EXPECT_EQ(static_cast<Num*>(token1.get())->value_, 0);
  EXPECT_EQ(token2->tag_, tag::kNum);
  EXPECT_EQ(static_cast<Num*>(token2.get())->value_, 123);
}

TEST(LexerTest, RealNumber) {
  Lexer lex = Lexer();
  lex.ReadCodes("0.1 123.3");
  std::unique_ptr<Token> token1 = lex.Scan();
  std::unique_ptr<Token> token2 = lex.Scan();

  EXPECT_EQ(token1->tag_, tag::kReal);
  EXPECT_FLOAT_EQ(static_cast<Real*>(token1.get())->value_, 0.1);
  EXPECT_EQ(token2->tag_, tag::kReal);
  EXPECT_FLOAT_EQ(static_cast<Real*>(token2.get())->value_, 123.3);
}

TEST(LexerTest, Identifier) {
  Lexer lex = Lexer();
  lex.ReadCodes("Id123Id123");
  std::unique_ptr<Token> token1 = lex.Scan();

  EXPECT_EQ(token1->tag_, tag::kId);
  EXPECT_EQ(static_cast<Word*>(token1.get())->lexeme_, "Id123Id123");
}

TEST(LexerTest, LogicalOperator_And) {
  Lexer lex = Lexer();
  lex.ReadCodes("& &&");
  std::unique_ptr<Token> token1 = lex.Scan();
  std::unique_ptr<Token> token2 = lex.Scan();

  EXPECT_EQ(token1->tag_, '&');
  EXPECT_EQ(token2->tag_, tag::kAnd);
  EXPECT_EQ(static_cast<Word*>(token2.get())->lexeme_, "&&");
}

TEST(LexerTest, LogicalOperator_Or) {
  Lexer lex = Lexer();
  lex.ReadCodes("| ||");
  std::unique_ptr<Token> token1 = lex.Scan();
  std::unique_ptr<Token> token2 = lex.Scan();

  EXPECT_EQ(token1->tag_, '|');
  EXPECT_EQ(token2->tag_, tag::kOr);
  EXPECT_EQ(static_cast<Word*>(token2.get())->lexeme_, "||");
}

TEST(LexerTest, LogicalOperator_Eq) {
  Lexer lex = Lexer();
  lex.ReadCodes("= ==");
  std::unique_ptr<Token> token1 = lex.Scan();
  std::unique_ptr<Token> token2 = lex.Scan();

  EXPECT_EQ(token1->tag_, '=');
  EXPECT_EQ(token2->tag_, tag::kEq);
  EXPECT_EQ(static_cast<Word*>(token2.get())->lexeme_, "==");
}

TEST(LexerTest, LogicalOperator_Ne) {
  Lexer lex = Lexer();
  lex.ReadCodes("! !=");
  std::unique_ptr<Token> token1 = lex.Scan();
  std::unique_ptr<Token> token2 = lex.Scan();

  EXPECT_EQ(token1->tag_, '!');
  EXPECT_EQ(token2->tag_, tag::kNe);
  EXPECT_EQ(static_cast<Word*>(token2.get())->lexeme_, "!=");
}

TEST(LexerTest, LogicalOperator_Lt) {
  Lexer lex = Lexer();
  lex.ReadCodes("< <=");
  std::unique_ptr<Token> token1 = lex.Scan();
  std::unique_ptr<Token> token2 = lex.Scan();

  EXPECT_EQ(token1->tag_, '<');
  EXPECT_EQ(token2->tag_, tag::kLe);
  EXPECT_EQ(static_cast<Word*>(token2.get())->lexeme_, "<=");
}

TEST(LexerTest, Identifier_If) {
  Lexer lex = Lexer();
  lex.ReadCodes("if");
  std::unique_ptr<Token> token1 = lex.Scan();

  EXPECT_EQ(token1->tag_, tag::kIf);
  EXPECT_EQ(static_cast<Word*>(token1.get())->lexeme_, "if");
}

TEST(LexerTest, Identifier_Else) {
  Lexer lex = Lexer();
  lex.ReadCodes("else");
  std::unique_ptr<Token> token1 = lex.Scan();

  EXPECT_EQ(token1->tag_, tag::kElse);
  EXPECT_EQ(static_cast<Word*>(token1.get())->lexeme_, "else");
}

TEST(LexerTest, Identifier_Do) {
  Lexer lex = Lexer();
  lex.ReadCodes("do");
  std::unique_ptr<Token> token1 = lex.Scan();

  EXPECT_EQ(token1->tag_, tag::kDo);
  EXPECT_EQ(static_cast<Word*>(token1.get())->lexeme_, "do");
}

TEST(LexerTest, Identifier_While) {
  Lexer lex = Lexer();
  lex.ReadCodes("while");
  std::unique_ptr<Token> token1 = lex.Scan();

  EXPECT_EQ(token1->tag_, tag::kWhile);
  EXPECT_EQ(static_cast<Word*>(token1.get())->lexeme_, "while");
}

TEST(LexerTest, Identifier_Break) {
  Lexer lex = Lexer();
  lex.ReadCodes("break");
  std::unique_ptr<Token> token1 = lex.Scan();

  EXPECT_EQ(token1->tag_, tag::kBreak);
  EXPECT_EQ(static_cast<Word*>(token1.get())->lexeme_, "break");
}

TEST(LexerTest, Identifier_True) {
  Lexer lex = Lexer();
  lex.ReadCodes("true");
  std::unique_ptr<Token> token1 = lex.Scan();

  EXPECT_EQ(token1->tag_, tag::kTrue);
  EXPECT_EQ(static_cast<Word*>(token1.get())->lexeme_, "true");
}

TEST(LexerTest, Identifier_False) {
  Lexer lex = Lexer();
  lex.ReadCodes("false");
  std::unique_ptr<Token> token1 = lex.Scan();

  EXPECT_EQ(token1->tag_, tag::kFalse);
  EXPECT_EQ(static_cast<Word*>(token1.get())->lexeme_, "false");
}

}  // namespace lexer
}  // namespace intellgraph
