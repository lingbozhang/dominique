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
#ifndef INTELLGRAPH_SRC_PARSER_STMT_WHILE_H_
#define INTELLGRAPH_SRC_PARSER_STMT_WHILE_H_

#include "src/parser/expr/expr.h"
#include "src/parser/stmt/stmt.h"

namespace intellgraph {
namespace inter {

class While : public Stmt {
 public:
  While();
  While(const While& obj);
  While(While&& obj);
  While& operator=(const While& obj);
  While& operator=(While&& obj);
  ~While() override;

  std::unique_ptr<Stmt> Clone() const override {
    return std::make_unique<While>(*this);
  }

  void Init(std::unique_ptr<Expr> expr, std::unique_ptr<Stmt> stmt);
  void Gen(int b, int a) override;

  std::unique_ptr<Expr> expr_;
  std::unique_ptr<Stmt> stmt_;
};

}  // namespace inter
}  // namespace intellgraph

#endif  // INTELLGRAPH_SRC_PARSER_STMT _WHILE_H_