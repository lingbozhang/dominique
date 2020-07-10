/* Copyright 2021 The IntellGraph Authors. All Rights Reserved.
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
#ifndef INTELLGRAPH_SRC_LEXER_TOKEN_H_
#define INTELLGRAPH_SRC_LEXER_TOKEN_H_

#include <map>
#include <memory>
#include <string>

#include "src/lexer/tag.h"

namespace intellgraph {
namespace lexer {

class Token {
 public:
  Token(int t) : tag_(t) {}
  Token(const Token &token) = default;
  Token &operator=(const Token &token) = default;
  virtual ~Token() = default;

  bool operator==(const Token &token) const { return tag_ == token.tag_; }
  bool operator!=(const Token &token) const { return !(*this == token); }

  virtual std::unique_ptr<Token> Clone() const {
    return std::make_unique<Token>(*this);
  }

  virtual std::string ToString() const {
    std::string s(1, (char)tag_);
    return s;
  }

  int tag_;
};

class Num : public Token {
 public:
  Num(int value) : Token(tag::kNum), value_(value) {}
  Num(const Num &num) = default;
  Num &operator=(const Num &num);
  ~Num() override = default;

  bool operator==(const Num &num) const;
  bool operator!=(const Num &num) const;

  std::unique_ptr<Token> Clone() const override {
    return std::make_unique<Num>(*this);
  }

  std::string ToString() const override { return std::to_string(value_); }

  int value_;
};

class Real : public Token {
 public:
  Real(float value) : Token(tag::kReal), value_(value) {}
  Real(const Real &real) = default;
  Real &operator=(const Real &real);
  ~Real() override = default;

  bool operator==(const Real &real) const;
  bool operator!=(const Real &real) const;

  std::unique_ptr<Token> Clone() const override {
    return std::make_unique<Real>(*this);
  }

  std::string ToString() const override { return std::to_string(value_); }

  float value_;
};

class Word : public Token {
 public:
   static Word And();
   static Word Or();
   static Word Eq();
   static Word Ne();
   static Word Le();
   static Word Ge();
   static Word Minus();
   static Word True();
   static Word False();
   static Word Temp();

   Word(const std::string &lexeme, int tag);
   Word(std::string &&lexeme, int tag);
   Word(const Word &word) = default;
   Word &operator=(const Word &word);
   ~Word() override;

   bool operator==(const Word &word) const;
   bool operator!=(const Word &word) const;
   // Required by the map container
   bool operator<(const Word &word) const;

   std::unique_ptr<Token> Clone() const override {
     return std::make_unique<Word>(*this);
  }

  std::string ToString() const override { return lexeme_; }

  std::string lexeme_;
};

}  // namespace lexer
}  // namespace intellgraph

#endif  // INTELLGRAPH_SRC_LEXER_TOKEN_H_
