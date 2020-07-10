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
#include "src/parser/expr/op.h"
#include "src/parser/expr/temp.h"

namespace intellgraph {
namespace inter {

Op::Op(std::unique_ptr<lexer::Token> token, std::unique_ptr<symbols::Type> type)
    : Expr(std::move(token), std::move(type)) {}
Op::Op(const Op &op) : Expr(op.op_->Clone(), op.type_->CloneType()) {}
Op& Op::operator=(const Op& op) {
  Expr::operator=(op);
  return *this;
}
Op::~Op() = default;

bool Op::operator==(const Op &op) const { return Expr::operator==(op); }

bool Op::operator!=(const Op &op) const { return !(*this == op); }

std::unique_ptr<Expr> Op::Reduce() {
  std::unique_ptr<Expr> x = this->Gen();
  std::unique_ptr<Temp> t = std::make_unique<Temp>(this->type_->CloneType());
  this->Emit(t->ToString() + " = " + x->ToString());
  return t;
}

}  // namespace inter
}  // namespace intellgraph
