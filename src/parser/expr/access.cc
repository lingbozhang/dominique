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
      array_(std::move(array)), index_(std::move(index)) {}
Access::Access(const Access &access)
    : Op(access.op_->Clone(), access.type_->CloneType()),
      array_(access.array_->CloneId()), index_(access.index_->Clone()) {}
Access &Access::operator=(const Access &access) {
  Op::operator=(access);
  array_ = access.array_->CloneId();
  index_ = access.index_->Clone();
  return *this;
}
Access::~Access() = default;

bool Access::operator==(const Access &obj) const {
  return Expr::operator==(obj) && *array_ == *obj.array_ &&
         *index_ == *obj.index_;
}
bool Access::operator!=(const Access &obj) const { return !(*this == obj); }

std::unique_ptr<Expr> Access::Gen() {
  return std::make_unique<Access>(array_->CloneId(), index_->Reduce(),
                                  type_->CloneType());
}

void Access::Jumping(int t, int f) {
  this->EmitJumps(this->Reduce()->ToString(), t, f);
}

}  // namespace inter
}  // namespace intellgraph
