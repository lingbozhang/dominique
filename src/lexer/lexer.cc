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

#include <iostream>
#include <memory>

#include "src/symbol/type.h"
#include "src/util.h"

namespace intellgraph {
namespace lexer {

Lexer::Lexer() {
  Reserve(std::make_unique<Word>("if", tag::kIf));
  Reserve(std::make_unique<Word>("else", tag::kElse));
  Reserve(std::make_unique<Word>("while", tag::kWhile));
  Reserve(std::make_unique<Word>("do", tag::kDo));
  Reserve(std::make_unique<Word>("break", tag::kBreak));
  Reserve(std::make_unique<Word>(Word::True()));
  Reserve(std::make_unique<Word>(Word::False()));
  // types
  Reserve(static_cast_unique_ptr<Word>(symbols::Type::Int().Clone()));
  Reserve(static_cast_unique_ptr<Word>(symbols::Type::Float().Clone()));
  Reserve(static_cast_unique_ptr<Word>(symbols::Type::Char().Clone()));
  Reserve(static_cast_unique_ptr<Word>(symbols::Type::Bool().Clone()));
  //
  str_iter_ = str_.begin();
}

bool Lexer::ReadCh(char c) {
  if (!ReadCh() || peek_ != c) {
    return false;
  }
  peek_ = ' ';
  return true;
}

void Lexer::ReadCodes(const std::string& codes) {
  str_ = codes;
  str_iter_ = str_.begin();
}

std::unique_ptr<Token> Lexer::Scan() {
  // Removes space, tab and new line characters, increases line number if a new
  // line character is scanned.
  do {
    if (peek_ == ' ' || peek_ == '\t') {
      continue;
    } else if (peek_ == '\n') {
      line_num_++;
    } else {
      break;
    }
  } while (ReadCh());
  // Reads a logical operator
  switch (peek_) {
    case '&':
      if (ReadCh('&')) {
        return Word::And().Clone();
      } else {
        return std::make_unique<Token>('&');
      }
    case '|':
      if (ReadCh('|')) {
        return Word::Or().Clone();
      } else {
        return std::make_unique<Token>('|');
      }
    case '=':
      if (ReadCh('=')) {
        return Word::Eq().Clone();
      } else {
        return std::make_unique<Token>('=');
      }
    case '!':
      if (ReadCh('=')) {
        return Word::Ne().Clone();
      } else {
        return std::make_unique<Token>('!');
      }
    case '<':
      if (ReadCh('=')) {
        return Word::Le().Clone();
      } else {
        return std::make_unique<Token>('<');
      }
    case '>':
      if (ReadCh('=')) {
        return Word::Ge().Clone();
      } else {
        return std::make_unique<Token>('>');
      }
  }
  // Reads an integer or a real number in a following format:
  // XX.XXXX
  // where X represents a digit. A real number must start with a digit.
  if (std::isdigit(peek_)) {
    int value = 0;
    do {
      value = 10 * value + int(peek_ - '0');
    } while (ReadCh() && std::isdigit(peek_));
    if (peek_ != '.') return std::make_unique<Num>(value);
    float x = value;
    float d = 10;
    while (ReadCh()) {
      if (!std::isdigit(peek_)) break;
      x = x + int(peek_ - '0') / d;
      d *= 10;
    }
    return std::make_unique<Real>(x);
  }
  // Reads an identifier that starts with an alphabetic character and follows by
  // alphanumeric characters
  if (std::isalpha(peek_)) {
    std::string lexeme = "";
    do {
      lexeme += peek_;
    } while (ReadCh() && std::isalnum(peek_));
    auto result =
        words.try_emplace(lexeme, std::make_unique<Word>(lexeme, tag::kId));
    return result.first->second->Clone();
  }
  std::unique_ptr<Token> token = std::make_unique<Token>(peek_);
  peek_ = ' ';
  return token;
}

void Lexer::Reserve(std::unique_ptr<Word> wd) {
  words.try_emplace(wd->lexeme_, std::move(wd));
}

bool Lexer::ReadCh() {
  if (str_iter_ != str_.end()) {
    peek_ = *str_iter_;
    str_iter_++;
    return true;
  }
  peek_ = ' ';
  return false;
}

int Lexer::line_num_ = 1;

}  // namespace lexer
}  // namespace intellgraph
