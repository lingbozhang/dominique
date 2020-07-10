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
#include "src/lexer/token.h"

namespace intellgraph {
namespace lexer {

Num &Num::operator=(const Num &num) {
  Token::operator=(num);
  value_ = num.value_;
  return *this;
}

bool Num::operator==(const Num &num) const {
  return Token::operator==(num) && value_ == num.value_;
}

bool Num::operator!=(const Num &num) const { return !(*this == num); }

Real &Real::operator=(const Real &real) {
  Token::operator=(real);
  value_ = real.value_;
  return *this;
}

bool Real::operator==(const Real &real) const {
  return Token::operator==(real) && value_ == real.value_;
}

bool Real::operator!=(const Real &real) const { return !(*this == real); }

Word Word::And() {
  static const Word kAnd = Word("&&", tag::kAnd);
  return kAnd;
}
Word Word::Or() {
  static const Word kOr = Word("||", tag::kOr);
  return kOr;
}
Word Word::Eq() {
  static const Word kEq = Word("==", tag::kEq);
  return kEq;
}
Word Word::Ne() {
  static const Word kNe = Word("!=", tag::kNe);
  return kNe;
}
Word Word::Le() {
  static const Word kLe = Word("<=", tag::kLe);
  return kLe;
}
Word Word::Ge() {
  static const Word kGe = Word(">=", tag::kGe);
  return kGe;
}
Word Word::Minus() {
  static const Word kMinus = Word("minus", tag::kMinus);
  return kMinus;
}
Word Word::True() {
  static const Word kTrue = Word("true", tag::kTrue);
  return kTrue;
}
Word Word::False() {
  static const Word kFalse = Word("false", tag::kFalse);
  return kFalse;
}
Word Word::Temp() {
  static const Word kTemp = Word("t", tag::kTemp);
  return kTemp;
}

Word::Word(const std::string &lexeme, int tag) : Token(tag), lexeme_(lexeme) {}

Word::Word(std::string &&lexeme, int tag)
    : Token(tag), lexeme_(std::move(lexeme)) {}

Word &Word::operator=(const Word &word) {
  Token::operator=(word);
  lexeme_ = word.lexeme_;
  return *this;
}

Word::~Word() = default;

bool Word::operator==(const Word &word) const {
  return Token::operator==(word) && lexeme_ == word.lexeme_;
}

bool Word::operator!=(const Word &word) const { return !(*this == word); }
bool Word::operator<(const Word &word) const {
  return this->lexeme_ < word.lexeme_;
}

}  // namespace lexer
}  // namespace intellgraph
