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
#include "src/parser/expr/not.h"

namespace intellgraph {
namespace inter {

Not::Not(std::unique_ptr<lexer::Token> token, std::unique_ptr<Expr> expr)
    : Logical(std::move(token), expr->Clone(), std::move(expr)) {}
Not::Not(const Not &obj)
    : Logical(obj.op_->Clone(), obj.expr1_->Clone(), obj.expr2_->Clone()) {}
Not &Not::operator=(const Not &obj) {
  Logical::operator=(obj);
  return *this;
}
Not::~Not() = default;

bool Not::operator==(const Not &obj) const { return Logical::operator==(obj); }

bool Not::operator!=(const Not &obj) const { return !(*this == obj); }

}  // namespace inter
}  // namespace intellgraph
