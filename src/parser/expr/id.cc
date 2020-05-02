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
#include "src/parser/expr/id.h"

namespace intellgraph {
namespace inter {

Id::Id(std::unique_ptr<lexer::Word> token, std::unique_ptr<symbols::Type> type,
       int offset)
    : Expr(std::move(token), std::move(type)), offset_(offset) {}
Id::Id(const Id& id)
    : Expr(id.op_->Clone(), id.type_->CloneType()), offset_(id.offset_) {}
Id::Id(Id&& id)
    : Expr(std::move(id.op_), std::move(id.type_)),
      offset_(std::move(id.offset_)) {}
Id& Id::operator=(const Id& id) {
  Expr::operator=(id);
  offset_ = id.offset_;
  return *this;
}
Id& Id::operator=(Id&& id) {
  Expr::operator=(std::move(id));
  offset_ = std::move(id.offset_);
  return *this;
}
Id::~Id() = default;

bool Id::operator==(const Id& id) const {
  return Expr::operator==(id) && offset_ == id.offset_;
}
bool Id::operator!=(const Id& id) const { return !(*this == id); }

}  // namespace inter
}  // namespace intellgraph
