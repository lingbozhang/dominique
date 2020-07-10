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
#include "src/parser/expr/expr.h"

namespace intellgraph {
namespace inter {

Expr::Expr(std::unique_ptr<lexer::Token> op,
           std::unique_ptr<symbols::Type> type)
    : op_(std::move(op)), type_(std::move(type)) {}
Expr::Expr(const Expr &expr)
    : op_(expr.op_->Clone()), type_(expr.type_->CloneType()) {}
Expr &Expr::operator=(const Expr &expr) {
  op_ = expr.op_->Clone();
  type_ = expr.type_->CloneType();
  return *this;
}
Expr::~Expr() = default;

bool Expr::operator==(const Expr& expr) const {
  return *op_ == *expr.op_ && *type_ == *expr.type_;
}
bool Expr::operator!=(const Expr& expr) const { return !(*this == expr); }

std::unique_ptr<Expr> Expr::Gen() {
  return std::make_unique<Expr>(this->op_->Clone(), this->type_->CloneType());
}

std::unique_ptr<Expr> Expr::Reduce() {
  return std::make_unique<Expr>(this->op_->Clone(), this->type_->CloneType());
}

std::unique_ptr<Expr> Expr::Clone() const {
  return std::make_unique<Expr>(op_->Clone(), type_->CloneType());
}
std::string Expr::ToString() const { return op_->ToString(); }

void Expr::Jumping(int t, int f) { EmitJumps(this->ToString(), t, f); }
void Expr::EmitJumps(const std::string& test, int t, int f) {
  if (t != 0 && f != 0) {
    this->Emit("if " + test + " goto L" + std::to_string(t));
    this->Emit("goto L" + std::to_string(f));
  } else if (t != 0) {
    this->Emit("if " + test + " goto L" + std::to_string(t));
  } else if (f != 0) {
    this->Emit("iffalse " + test + " goto L" + std::to_string(f));
  }
}

}  // namespace inter
}  // namespace intellgraph
