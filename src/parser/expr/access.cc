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
#include "src/parser/expr/access.h"

namespace intellgraph {
namespace inter {

Access::Access(std::unique_ptr<Id> array, std::unique_ptr<Expr> index,
               std::unique_ptr<symbols::Type> type)
    : Op(std::make_unique<lexer::Word>("[]", lexer::tag::kIndex),
         std::move(type)),
      array_(std::move(array)),
      index_(std::move(index)) {}
Access::Access(const Access& obj)
    : Op(obj.op_->Clone(), obj.type_->CloneType()),
      array_(obj.array_->CloneId()),
      index_(obj.index_->Clone()) {}
Access::Access(Access&& obj)
    : Op(std::move(obj.op_), std::move(obj.type_)),
      array_(std::move(obj.array_)),
      index_(std::move(obj.index_)) {}
Access& Access::operator=(const Access& obj) {
  Op::operator=(obj);
  array_ = obj.array_->CloneId();
  index_ = obj.index_->Clone();
  return *this;
}
Access& Access::operator=(Access&& obj) {
  Op::operator=(std::move(obj));
  array_ = std::move(obj.array_);
  index_ = std::move(obj.index_);
  return *this;
}
Access::~Access() = default;

std::unique_ptr<Expr> Access::Gen() {
  return std::make_unique<Access>(array_->CloneId(), index_->Reduce(),
                                  this->type_->CloneType());
}

void Access::Jumping(int t, int f) {
  this->EmitJumps(this->Reduce()->ToString(), t, f);
}

}  // namespace inter
}  // namespace intellgraph