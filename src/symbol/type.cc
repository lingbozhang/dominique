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

const Type &Type::Int() {
  static const Type kInt = Type(TypeId::kInt);
  return kInt;
}

const Type &Type::Float() {
  static const Type kFloat = Type(TypeId::kFloat);
  return kFloat;
}

const Type &Type::Char() {
  static const Type kChar = Type(TypeId::kChar);
  return kChar;
}

const Type &Type::Bool() {
  static const Type kBool = Type(TypeId::kBool);
  return kBool;
}

const Type &Type::Null() {
  static const Type kNull = Type(TypeId::kNull);
  return kNull;
}

bool Type::IsNumeric(const Type &p) {
  if (p == Type::Char() || p == Type::Int() || p == Type::Float()) {
    return true;
  }
  return false;
}

llvm::IntegerType *Type::GenIntTy(llvm::LLVMContext &context) {
  return llvm::Type::getInt32Ty(context);
}

llvm::Type *Type::GenFloatTy(llvm::LLVMContext &context) {
  return llvm::Type::getFloatTy(context);
}

llvm::IntegerType *Type::GenCharTy(llvm::LLVMContext &context) {
  return llvm::Type::getInt8Ty(context);
}

llvm::IntegerType *Type::GenBoolTy(llvm::LLVMContext &context) {
  return llvm::Type::getInt8Ty(context);
}

Type Type::Max(const Type &lf, const Type &rt) {
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

Type::Type(TypeId id) : lexer::Word("", lexer::tag::kBasic), id_(id) {
  switch (id_) {
  case TypeId::kInt:
    width_ = 4;
    return;
  case TypeId::kFloat:
    width_ = 8;
    return;
  case TypeId::kChar:
    width_ = 1;
    return;
  case TypeId::kBool:
    width_ = 1;
    return;
  case TypeId::kNull:
    width_ = 0;
    return;
  case TypeId::kUndefined:
  default:
    exit(1);
  }
}

Type::Type(const std::string &lexeme, int tag, int width)
    : lexer::Word(lexeme, tag), id_(TypeId::kUndefined), width_(width) {}

Type::Type(const Type &type)
    : lexer::Word(type.lexeme_, type.tag_), id_(type.id_), width_(type.width_) {
}

Type& Type::operator=(const Type& type) {
  if (*this != type) {
    lexer::Word::operator=(type);
    id_ = type.id_;
    width_ = type.width_;
  }
  return *this;
}

Type::~Type() = default;

bool Type::operator==(const Type& type) const {
  return lexer::Word::operator==(type) && id_ == type.id_ &&
         width_ == type.width_;
}

bool Type::operator!=(const Type& type) const { return !(*this == type); }

}  // namespace symbols
}  // namespace intellgraph
