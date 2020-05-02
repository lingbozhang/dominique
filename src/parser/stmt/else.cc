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
#include "src/parser/stmt/else.h"

namespace intellgraph {
namespace inter {

Else::Else(std::unique_ptr<Expr> expr, std::unique_ptr<Stmt> stmt1,
           std::unique_ptr<Stmt> stmt2)
    : expr_(std::move(expr)),
      stmt1_(std::move(stmt1)),
      stmt2_(std::move(stmt2)) {
  if (*expr_->type_ != symbols::Type::Bool()) {
    expr_->Error("boolean required in if");
  }
}
Else::Else(const Else& obj)
    : expr_(obj.expr_->Clone()),
      stmt1_(obj.stmt1_->Clone()),
      stmt2_(obj.stmt2_->Clone()) {}
Else::Else(Else&& obj)
    : expr_(std::move(obj.expr_)),
      stmt1_(std::move(obj.stmt1_)),
      stmt2_(std::move(obj.stmt2_)) {}
Else& Else::operator=(const Else& obj) {
  Stmt::operator=(obj);
  expr_ = obj.expr_->Clone();
  stmt1_ = obj.stmt1_->Clone();
  stmt2_ = obj.stmt2_->Clone();
  return *this;
}
Else& Else::operator=(Else&& obj) {
  Stmt::operator=(obj);
  expr_ = std::move(obj.expr_);
  stmt1_ = std::move(obj.stmt1_);
  stmt2_ = std::move(obj.stmt2_);
  return *this;
}
Else::~Else() = default;

void Else::Gen(int b, int a) {
  int label1 = this->NewLabel();
  int label2 = this->NewLabel();
  expr_->Jumping(0, label2);
  this->EmitLabel(label1);
  stmt1_->Gen(label1, a);
  this->Emit("goto L" + std::to_string(a));
  this->EmitLabel(label2);
  stmt2_->Gen(label2, a);
}

}  // namespace inter
}  // namespace intellgraph