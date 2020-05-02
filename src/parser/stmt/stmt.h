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
#ifndef INTELLGRAPH_SRC_PARSER_STMT_STMT_H_
#define INTELLGRAPH_SRC_PARSER_STMT_STMT_H_

#include "src/parser/node.h"

namespace intellgraph {
namespace inter {

class Stmt : public Node {
 public:
  static Stmt Null() {
    static const Stmt kNull = Stmt(-1);
    return kNull;
  }
  static Stmt Enclosing() {
    static const Stmt kEnclosing = Stmt::Null();
    return kEnclosing;
  }

  Stmt() = default;
  explicit Stmt(int after);
  Stmt(const Stmt& obj);
  Stmt(Stmt&& obj);
  Stmt& operator=(const Stmt& obj);
  Stmt& operator=(Stmt&& obj);
  ~Stmt() override;

  virtual std::unique_ptr<Stmt> Clone() const {
    return std::make_unique<Stmt>(*this);
  }

  bool operator==(const Stmt& stmt) { return after_ == stmt.after_; }
  bool operator!=(const Stmt& stmt) { return after_ != stmt.after_; }

  virtual void Gen(int a, int b) {}

  int after_ = 0;
};

}  // namespace inter
}  // namespace intellgraph

#endif  // INTELLGRAPH_SRC_PARSE_STMT_STMT_H_