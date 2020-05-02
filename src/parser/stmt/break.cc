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
#include "src/parser/stmt/break.h"

namespace intellgraph {
namespace inter {

Break::Break() {
  if (Stmt::Enclosing() == Stmt::Null()) {
    this->Error("Unenclosed break!");
  }
  stmt_ = Stmt::Enclosing().Clone();
}
Break::~Break() = default;

void Break::Gen(int b, int a) {
  this->Emit("goto L" + std::to_string(stmt_->after_));
}

}  // namespace inter
}  // namespace intellgraph