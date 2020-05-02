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
#include "src/parser/expr/logical.h"

namespace intellgraph {
namespace inter {

Logical::Logical(std::unique_ptr<lexer::Token> token,
                 std::unique_ptr<Expr> expr1, std::unique_ptr<Expr> expr2)
    : Expr(std::move(token), nullptr),
      expr1_(std::move(expr1)),
      expr2_(std::move(expr2)) {
  std::unique_ptr<symbols::Type> type =
      Check(expr1_->type_.get(), expr2_->type_.get());
  if (*type == symbols::Type::Null()) {
    this->Error("Type Error");
  }
  this->type_ = type->CloneType();
}
Logical::Logical(const Logical& logical)
    : Expr(logical.op_->Clone(), logical.type_->CloneType()),
      expr1_(logical.expr1_->Clone()),
      expr2_(logical.expr2_->Clone()) {}
Logical::Logical(Logical&& logical)
    : Expr(std::move(logical.op_), std::move(logical.type_)),
      expr1_(std::move(logical.expr1_)),
      expr2_(std::move(logical.expr2_)) {}
Logical& Logical::operator=(const Logical& logical) {
  Expr::operator=(logical);
  expr1_ = logical.expr1_->Clone();
  expr2_ = logical.expr2_->Clone();
  return *this;
}
Logical& Logical::operator=(Logical&& logical) {
  Expr::operator=(std::move(logical));
  expr1_ = std::move(logical.expr1_);
  expr2_ = std::move(logical.expr2_);
  return *this;
}
Logical::~Logical() = default;

std::unique_ptr<Expr> Logical::Gen() {
  int f = this->NewLabel();
  int a = this->NewLabel();
  std::unique_ptr<Temp> temp = std::make_unique<Temp>(this->type_->CloneType());
  this->Jumping(0, f);
  this->Emit(temp->ToString() + " = true");
  this->Emit("goto L" + std::to_string(a));
  this->EmitLabel(f);
  this->Emit(temp->ToString() + " = false");
  this->EmitLabel(a);
  return temp;
}

std::unique_ptr<symbols::Type> Logical::Check(const symbols::Type* type1,
                                              const symbols::Type* type2) {
  if (*type1 == symbols::Type::Bool() && *type2 == symbols::Type::Bool()) {
    return symbols::Type::Bool().CloneType();
  } else {
    return symbols::Type::Null().CloneType();
  }
}

}  // namespace inter
}  // namespace intellgraph