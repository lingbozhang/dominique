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
#include "src/parser/expr/rel.h"

namespace intellgraph {
namespace inter {
Rel::Rel(std::unique_ptr<lexer::Token> token, std::unique_ptr<Expr> expr1,
         std::unique_ptr<Expr> expr2)
    : Logical(std::move(token), std::move(expr1), std::move(expr2)) {}
Rel::Rel(const Rel& obj)
    : Logical(obj.op_->Clone(), obj.expr1_->Clone(), obj.expr2_->Clone()) {}
Rel::Rel(Rel&& obj)
    : Logical(std::move(obj.op_), std::move(obj.expr1_),
              std::move(obj.expr2_)) {}
Rel& Rel::operator=(const Rel& obj) {
  Logical::operator=(obj);
  return *this;
}
Rel& Rel::operator=(Rel&& obj) {
  Logical::operator=(std::move(obj));
  return *this;
}
Rel::~Rel() = default;

std::unique_ptr<symbols::Type> Rel::Check(const symbols::Type* type1,
                                          const symbols::Type* type2) {
  if (dynamic_cast<const symbols::Array*>(type1) != nullptr ||
      dynamic_cast<const symbols::Array*>(type2) != nullptr) {
    return symbols::Type::Null().CloneType();
  } else if (*type1 == *type2) {
    return symbols::Type::Bool().CloneType();
  } else {
    return symbols::Type::Null().CloneType();
  }
}

void Rel::Jumping(int t, int f) {
  std::unique_ptr<Expr> a = this->expr1_->Reduce();
  std::unique_ptr<Expr> b = this->expr2_->Reduce();
  const std::string test =
      a->ToString() + " " + this->op_->ToString() + " " + b->ToString();
  this->EmitJumps(test, t, f);
}

}  // namespace inter
}  // namespace intellgraph