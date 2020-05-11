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
#ifndef INTELLGRAPH_SRC_PARSER_EXPR_OP_H_
#define INTELLGRAPH_SRC_PARSER_EXPR_OP_H_

#include <memory>

#include "src/parser/expr/expr.h"
#include "src/parser/expr/temp.h"

namespace intellgraph {
namespace inter {

class Op : public Expr {
 public:
  Op(std::unique_ptr<lexer::Token> token, std::unique_ptr<symbols::Type> type);
  Op(const Op& op);
  Op(Op&& op);
  Op& operator=(const Op& op);
  Op& operator=(Op&& op);
  ~Op() override;

  bool operator==(const Op &op) const;
  bool operator!=(const Op &op) const;

  std::unique_ptr<Expr> Clone() const override {
    return std::make_unique<Op>(*this);
  }

  std::unique_ptr<Expr> Reduce() final;
};

}  // namespace inter
}  // namespace intellgraph

#endif  // INTELLGRAPH_SRC_PARSER_EXPR_OP_H_
