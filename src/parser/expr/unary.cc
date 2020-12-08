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
#include "src/parser/expr/unary.h"

namespace intellgraph {
namespace inter {

Unary::Unary(std::unique_ptr<lexer::Token> token, std::unique_ptr<Expr> expr)
    : Op(std::move(token), nullptr), expr_(std::move(expr)) {
  symbols::Type type = symbols::Type::Max(symbols::Type::Int(), *expr_->type_);
  if (type == symbols::Type::Null()) {
    this->Error("Type Error");
  }
  this->type_ = type.CloneType();
}

Unary::Unary(const Unary &unary)
    : Op(unary.op_->Clone(), unary.type_->CloneType()),
      expr_(unary.expr_->Clone()) {}

Unary &Unary::operator=(const Unary &unary) {
  Op::operator=(unary);
  expr_ = unary.expr_->Clone();
  return *this;
}

Unary::~Unary() = default;

bool Unary::operator==(const Unary &unary) const {
  return Expr::operator==(unary) && Op::operator==(unary);
}

bool Unary::operator!=(const Unary &unary) const { return !(*this == unary); }

std::unique_ptr<Expr> Unary::Gen() {
  return std::make_unique<Unary>(this->op_->Clone(), expr_->Reduce());
}

}  // namespace inter
}  // namespace intellgraph
