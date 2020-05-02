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

namespace intellgraph {
namespace symbols {

Type::Type(const std::string& lexeme, int tag, int width)
    : lexer::Word(lexeme, tag), width_(width) {}
Type::Type(std::string&& lexeme, int tag, int width)
    : lexer::Word(std::move(lexeme), tag), width_(width) {}
Type& Type::operator=(const Type& type) {
  if (*this != type) {
    lexer::Word::operator=(type);
    width_ = type.width_;
  }
  return *this;
}
Type& Type::operator=(Type&& type) {
  if (*this != type) {
    width_ = type.width_;
    lexer::Word::operator=(std::move(type));
  }
  return *this;
}
Type::~Type() = default;

bool Type::operator==(const Type& type) const {
  return lexer::Word::operator==(type) && width_ == type.width_;
}
bool Type::operator!=(const Type& type) const { return !(*this == type); }

}  // namespace symbols
}  // namespace intellgraph