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
#include "src/parser/stmt/do.h"

namespace intellgraph {
namespace inter {

Do::Do() = default;
Do::Do(const Do& obj) : expr_(obj.expr_->Clone()), stmt_(obj.stmt_->Clone()) {}
Do& Do::operator=(const Do& obj) {
  Stmt::operator=(obj);
  expr_ = obj.expr_->Clone();
  stmt_ = obj.stmt_->Clone();
  return *this;
}
Do::~Do() = default;

void Do::Init(std::unique_ptr<Expr> expr, std::unique_ptr<Stmt> stmt) {
  expr_ = std::move(expr);
  stmt_ = std::move(stmt);
  if (*expr_->type_ != symbols::Type::Bool()) {
    expr_->Error("boolean required in do");
  }
}

void Do::Gen(int b, int a) {
  this->after_ = a;
  int label = this->NewLabel();
  stmt_->Gen(b, label);
  this->EmitLabel(label);
  expr_->Jumping(b, 0);
}

}  // namespace inter
}  // namespace intellgraph
