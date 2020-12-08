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
#include "src/parser/stmt/stmt.h"

namespace intellgraph {
namespace inter {

const Stmt &Stmt::Null() {
  static const Stmt kNull = Stmt(-1);
  return kNull;
}

const Stmt *&Stmt::Enclosing() {
  static const Stmt *kEnclosing = &Stmt::Null();
  return kEnclosing;
}

Stmt::Stmt(int after) : after_(after) {}

Stmt::Stmt(const Stmt& obj) : after_(obj.after_) {}

Stmt& Stmt::operator=(const Stmt& obj) {
  after_ = obj.after_;
  return *this;
}

Stmt::~Stmt() = default;

}  // namespace inter
}  // namespace intellgraph
