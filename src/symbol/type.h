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
#ifndef INTELLGRAPH_SRC_SYMBOL_TYPE_H_
#define INTELLGRAPH_SRC_SYMBOL_TYPE_H_

#include <string>

#include "src/lexer/token.h"

namespace intellgraph {
namespace symbols {

class Type : public lexer::Word {
 public:
  static Type Int() {
    static const Type kInt = Type("int", lexer::tag::kBasic, 4);
    return kInt;
  }
  static Type Float() {
    static const Type kFloat = Type("float", lexer::tag::kBasic, 8);
    return kFloat;
  }
  static Type Char() {
    static const Type kChar = Type("char", lexer::tag::kBasic, 1);
    return kChar;
  }
  static Type Bool() {
    static const Type kBool = Type("bool", lexer::tag::kBasic, 1);
    return kBool;
  }
  static Type Null() {
    static const Type kNull = Type("null", lexer::tag::kBasic, 0);
    return kNull;
  }

  static bool IsNumeric(const Type& p) {
    if (p == Type::Char() || p == Type::Int() || p == Type::Float()) {
      return true;
    }
    return false;
  }

  static Type Max(const Type& lf, const Type& rt) {
    if (!IsNumeric(lf) || !IsNumeric(rt)) {
      return Type::Null();
    } else if (lf == Type::Float() || rt == Type::Float()) {
      return Type::Float();
    } else if (lf == Type::Int() || rt == Type::Int()) {
      return Type::Int();
    } else {
      return Type::Char();
    }
  }

  Type(const std::string& lexeme, int tag, int width);
  Type(std::string&& lexeme, int tag, int width);
  Type(const Type& type) = default;
  Type(Type&& type) = default;
  Type& operator=(const Type& type);
  Type& operator=(Type&& type);
  ~Type() override;

  bool operator==(const Type& type) const;
  bool operator!=(const Type& type) const;

  std::unique_ptr<Token> Clone() const override {
    return std::make_unique<Type>(*this);
  }

  virtual std::unique_ptr<Type> CloneType() const {
    return std::make_unique<Type>(*this);
  }

  int width_;
};

}  // namespace symbols
}  // namespace intellgraph

#endif  // INTELLGRAPH_SRC_SYMBOL_TYPE_H_
