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
#include "src/parser/stmt/seq.h"

namespace intellgraph {
namespace inter {

Seq::Seq(std::unique_ptr<Stmt> stmt1, std::unique_ptr<Stmt> stmt2)
    : stmt1_(std::move(stmt1)), stmt2_(std::move(stmt2)) {}
Seq::Seq(const Seq& obj)
    : stmt1_(obj.stmt1_->Clone()), stmt2_(obj.stmt2_->Clone()) {}
Seq::Seq(Seq&& obj)
    : stmt1_(std::move(obj.stmt1_)), stmt2_(std::move(obj.stmt2_)) {}
Seq& Seq::operator=(const Seq& obj) {
  Stmt::operator=(obj);
  stmt1_ = obj.stmt1_->Clone();
  stmt2_ = obj.stmt2_->Clone();
  return *this;
}
Seq& Seq::operator=(Seq&& obj) {
  Stmt::operator=(std::move(obj));
  stmt1_ = std::move(obj.stmt1_);
  stmt2_ = std::move(obj.stmt2_);
  return *this;
}
Seq::~Seq() = default;

void Seq::Gen(int b, int a) {
  if (*stmt1_ == Stmt::Null()) {
    stmt2_->Gen(b, a);
  } else {
    int label = this->NewLabel();
    stmt1_->Gen(b, label);
    this->EmitLabel(label);
    stmt2_->Gen(label, a);
  }
}

}  // namespace inter
}  // namespace intellgraph