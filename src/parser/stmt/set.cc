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
#include "src/parser/stmt/set.h"

namespace intellgraph {
namespace inter {

Set::Set(std::unique_ptr<Id> id, std::unique_ptr<Expr> expr)
    : id_(std::move(id)), expr_(std::move(expr)) {
  std::unique_ptr<symbols::Type> type =
      Check(id_->type_.get(), expr_->type_.get());
  if (*type == symbols::Type::Null()) {
    this->Error("type error");
  }
}

Set::Set(const Set& obj)
    : id_(std::make_unique<Id>(*obj.id_)), expr_(obj.expr_->Clone()) {}

Set& Set::operator=(const Set& obj) {
  Stmt::operator=(obj);
  id_ = std::make_unique<Id>(*obj.id_);
  expr_ = obj.expr_->Clone();
  return *this;
}

Set::~Set() = default;

bool Set::operator==(const Set &obj) const {
  return *id_ == *obj.id_ && *expr_ == *obj.expr_;
}

bool Set::operator!=(const Set &obj) const { return !(*this == obj); }

std::unique_ptr<symbols::Type> Set::Check(const symbols::Type* type1,
                                          const symbols::Type* type2) const {
  if (symbols::Type::IsNumeric(*type1) && symbols::Type::IsNumeric(*type2)) {
    return type2->CloneType();
  } else if (*type1 == symbols::Type::Bool() &&
             *type2 == symbols::Type::Bool()) {
    return type2->CloneType();
  } else {
    return symbols::Type::Null().CloneType();
  }
}

void Set::Gen(int b, int a) {
  this->Emit(id_->ToString() + " = " + expr_->Gen()->ToString());
}

}  // namespace inter
}  // namespace intellgraph
