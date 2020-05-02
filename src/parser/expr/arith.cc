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
#include "src/parser/expr/arith.h"

namespace intellgraph {
namespace inter {

Arith::Arith(std::unique_ptr<lexer::Token> token, std::unique_ptr<Expr> expr1,
             std::unique_ptr<Expr> expr2)
    : Op(std::move(token), nullptr),
      expr1_(std::move(expr1)),
      expr2_(std::move(expr2)) {
  symbols::Type type = symbols::Type::Max(*expr1_->type_, *expr2_->type_);
  if (type == symbols::Type::Null()) {
    this->Error("Type Error");
  }
  this->type_ = type.CloneType();
}
Arith::Arith(const Arith& arith)
    : Op(arith.op_->Clone(), arith.type_->CloneType()),
      expr1_(arith.expr1_->Clone()),
      expr2_(arith.expr2_->Clone()) {}
Arith::Arith(Arith&& arith)
    : Op(std::move(arith.op_), std::move(arith.type_)),
      expr1_(std::move(arith.expr1_)),
      expr2_(std::move(arith.expr2_)) {}
Arith::~Arith() = default;

std::unique_ptr<Expr> Arith::Gen() {
  return std::make_unique<Arith>(this->op_->Clone(), expr1_->Reduce(),
                                 expr2_->Reduce());
}

}  // namespace inter
}  // namespace intellgraph