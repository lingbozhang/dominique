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
#include "src/parser/expr/constant.h"

namespace intellgraph {
namespace inter {

const Constant &Constant::True() {
  static const Constant kTrue =
      Constant(lexer::Word::True().Clone(), symbols::Type::Bool().CloneType());
  return kTrue;
}

const Constant &Constant::False() {
  static const Constant kFalse =
      Constant(lexer::Word::False().Clone(), symbols::Type::Bool().CloneType());
  return kFalse;
}

Constant::Constant(std::unique_ptr<lexer::Token> token,
                   std::unique_ptr<symbols::Type> type)
    : Expr(std::move(token), std::move(type)) {}

Constant::Constant(int i)
    : Expr(std::make_unique<lexer::Num>(i), symbols::Type::Int().CloneType()) {}

Constant::Constant(const Constant &constant)
    : Expr(constant.op_->Clone(), constant.type_->CloneType()) {}

Constant &Constant::operator=(const Constant &constant) {
  op_ = constant.op_->Clone();
  type_ = constant.type_->CloneType();
  return *this;
}

Constant::~Constant() = default;

bool Constant::operator==(const Constant& constant) const {
  return Expr::operator==(constant);
}

bool Constant::operator!=(const Constant& constant) const {
  return !(*this == constant);
}

void Constant::Jumping(int t, int f) {
  if (*this == Constant::True() && t != 0) {
    this->Emit("goto L" + std::to_string(t));
  } else if (*this == Constant::False() && f != 0) {
    this->Emit("goto L" + std::to_string(f));
  }
}

}  // namespace inter
}  // namespace intellgraph
