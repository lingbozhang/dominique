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
#ifndef INTELLGRAPH_SRC_PARSER_STMT_BREAK_H_
#define INTELLGRAPH_SRC_PARSER_STMT_BREAK_H_

#include "src/parser/stmt/stmt.h"

namespace intellgraph {
namespace inter {

class Break : public Stmt {
 public:
  Break();
  ~Break() override;

  std::unique_ptr<Stmt> Clone() const override {
    this->Error("Break clone is not defined!");
    return nullptr;
  }

  void Gen(int b, int a) override;

  const Stmt *stmt_;
};

}  // namespace inter
}  // namespace intellgraph

#endif  // INTELLGRAPH_SRC_PARSER_STMT_BREAK_H_
