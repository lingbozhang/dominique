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
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Type.h"

namespace intellgraph {
namespace symbols {

class Type : public lexer::Word {
 public:
   // Primitive types
   enum TypeId { kUndefined = 0, kInt, kFloat, kChar, kBool, kNull };
   static const Type &Int();
   static const Type &Float();
   static const Type &Char();
   static const Type &Bool();
   static const Type &Null();

   static llvm::IntegerType *GenIntTy(llvm::LLVMContext &context);
   static llvm::Type *GenFloatTy(llvm::LLVMContext &context);
   static llvm::IntegerType *GenCharTy(llvm::LLVMContext &context);
   static llvm::IntegerType *GenBoolTy(llvm::LLVMContext &context);

   static bool IsNumeric(const Type &p);
   static Type Max(const Type &lf, const Type &rt);

   Type(TypeId id);
   Type(const std::string &lexeme, int tag, int width);
   Type(const Type &type);
   Type &operator=(const Type &type);
   ~Type() override;

   bool operator==(const Type &type) const;
   bool operator!=(const Type &type) const;

   std::unique_ptr<Token> Clone() const override {
     return std::make_unique<Type>(*this);
   }

  virtual std::unique_ptr<Type> CloneType() const {
    return std::make_unique<Type>(*this);
  }

  TypeId GetTypeId() const { return id_; }

  TypeId id_;
  int width_;
};

}  // namespace symbols
}  // namespace intellgraph

#endif  // INTELLGRAPH_SRC_SYMBOL_TYPE_H_
