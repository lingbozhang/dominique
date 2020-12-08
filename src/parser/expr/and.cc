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
#include "src/parser/expr/and.h"

namespace intellgraph {
namespace inter {
And::And(std::unique_ptr<lexer::Token> token, std::unique_ptr<Expr> expr1,
         std::unique_ptr<Expr> expr2)
    : Logical(std::move(token), std::move(expr1), std::move(expr2)) {
  std::unique_ptr<symbols::Type> type =
      this->Check(expr1_->type_.get(), expr2_->type_.get());
  if (*type == symbols::Type::Null()) {
    this->Error("Type Error");
  }
  this->type_ = type->CloneType();
}

And::And(const And &obj)
    : Logical(obj.op_->Clone(), obj.expr1_->Clone(), obj.expr2_->Clone()) {
  this->type_ = obj.type_->CloneType();
}

And& And::operator=(const And& obj) {
  Logical::operator=(obj);
  this->type_ = obj.type_->CloneType();
  return *this;
}

And::~And() = default;

void And::Jumping(int t, int f) {
  int label = f != 0 ? f : this->NewLabel();
  this->expr1_->Jumping(0, label);
  this->expr2_->Jumping(t, f);
  if (f == 0) this->EmitLabel(label);
}

std::unique_ptr<symbols::Type> And::Check(const symbols::Type *type1,
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
