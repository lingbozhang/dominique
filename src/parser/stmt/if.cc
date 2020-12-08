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
#include "src/parser/stmt/if.h"

namespace intellgraph {
namespace inter {

If::If(std::unique_ptr<Expr> expr, std::unique_ptr<Stmt> stmt)
    : expr_(std::move(expr)), stmt_(std::move(stmt)) {
  if (*expr_->type_ != symbols::Type::Bool()) {
    expr_->Error("boolean required in if");
  }
}

If::If(const If& obj) : expr_(obj.expr_->Clone()), stmt_(obj.stmt_->Clone()) {}

If& If::operator=(const If& obj) {
  Stmt::operator=(obj);
  expr_ = obj.expr_->Clone();
  stmt_ = obj.stmt_->Clone();
  return *this;
}

If::~If() = default;

void If::Gen(int b, int a) {
  int label = this->NewLabel();
  expr_->Jumping(0, a);
  stmt_->Gen(label, a);
}

}  // namespace inter
}  // namespace intellgraph
