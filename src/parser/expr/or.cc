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
#include "src/parser/expr/or.h"

namespace intellgraph {
namespace inter {

Or::Or(std::unique_ptr<lexer::Token> token, std::unique_ptr<Expr> expr1,
       std::unique_ptr<Expr> expr2)
    : Logical(std::move(token), std::move(expr1), std::move(expr2)) {
  std::unique_ptr<symbols::Type> type =
      this->Check(expr1_->type_.get(), expr2_->type_.get());
  if (*type == symbols::Type::Null()) {
    this->Error("Type Error");
  }
  this->type_ = type->CloneType();
}

Or::Or(const Or &obj)
    : Logical(obj.op_->Clone(), obj.expr1_->Clone(), obj.expr2_->Clone()) {
  this->type_ = obj.type_->CloneType();
}

Or &Or::operator=(const Or &obj) {
  Logical::operator=(obj);
  this->type_ = obj.type_->CloneType();
  return *this;
}

Or::~Or() = default;

void Or::Jumping(int t, int f) {
  int label = t != 0 ? t : this->NewLabel();
  this->expr1_->Jumping(label, 0);
  this->expr2_->Jumping(t, f);
  if (t == 0) {
    this->EmitLabel(label);
  }
}

std::unique_ptr<symbols::Type> Or::Check(const symbols::Type *type1,
                                         const symbols::Type *type2) {
  // TypeCheck for the Logical class
  if (*type1 == symbols::Type::Bool() && *type2 == symbols::Type::Bool()) {
    return symbols::Type::Bool().CloneType();
  } else {
    return symbols::Type::Null().CloneType();
  }
}

}  // namespace inter
}  // namespace intellgraph
