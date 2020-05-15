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
#include "src/parser/stmt/set_elem.h"

namespace intellgraph {
namespace inter {

SetElem::SetElem(std::unique_ptr<Access> access, std::unique_ptr<Expr> expr)
    : access_(std::move(access)), expr_(std::move(expr)) {
  if (*Check(access_->type_.get(), expr_->type_.get()) ==
      symbols::Type::Null()) {
    this->Error("Type error");
  }
}
SetElem::SetElem(const SetElem& obj)
    : access_(std::make_unique<Access>(*obj.access_)),
      expr_(obj.expr_->Clone()) {}
SetElem::SetElem(SetElem&& obj)
    : access_(std::move(obj.access_)), expr_(std::move(obj.expr_)) {}
SetElem& SetElem::operator=(const SetElem& obj) {
  Stmt::operator=(obj);
  access_ = std::make_unique<Access>(*obj.access_);
  expr_ = obj.expr_->Clone();
  return *this;
}
SetElem& SetElem::operator=(SetElem&& obj) {
  Stmt::operator=(std::move(obj));
  access_ = std::move(obj.access_);
  expr_ = std::move(obj.expr_);
  return *this;
}
SetElem::~SetElem() = default;

bool SetElem::operator==(const SetElem &obj) const {
  return *access_ == *obj.access_ && *expr_ == *obj.expr_;
}
bool SetElem::operator!=(const SetElem &obj) const { return !(*this == obj); }

std::unique_ptr<symbols::Type> SetElem::Check(
    const symbols::Type* type1, const symbols::Type* type2) const {
  if (dynamic_cast<const symbols::Array*>(type1) != nullptr ||
      dynamic_cast<const symbols::Array*>(type2) != nullptr) {
    return symbols::Type::Null().CloneType();
  } else if (*type1 == *type2) {
    return type2->CloneType();
  } else if (symbols::Type::IsNumeric(*type1) &&
             symbols::Type::IsNumeric(*type2)) {
    return type2->CloneType();
  } else {
    return symbols::Type::Null().CloneType();
  }
}

void SetElem::Gen(int b, int a) {
  const std::string s1 = access_->index_->Reduce()->ToString();
  const std::string s2 = expr_->Reduce()->ToString();
  this->Emit(access_->array_->ToString() + " [ " + s1 + " ] = " + s2);
}

}  // namespace inter
}  // namespace intellgraph
