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
#ifndef INTELLGRAPH_SRC_PARSER_EXPR_UNARY_H_
#define INTELLGRAPH_SRC_PARSER_EXPR_UNARY_H_

#include "src/parser/expr/op.h"
#include "src/symbol/type.h"

namespace intellgraph {
namespace inter {

class Unary : public Op {
 public:
   Unary(std::unique_ptr<lexer::Token> token, std::unique_ptr<Expr> expr);
   Unary(const Unary &unary);
   Unary &operator=(const Unary &unary);
   ~Unary() override;

   bool operator==(const Unary &unary) const;
   bool operator!=(const Unary &unary) const;

   std::unique_ptr<Expr> Clone() const override {
     return std::make_unique<Unary>(*this);
  }

  std::string ToString() const override {
    return this->op_->ToString() + " " + expr_->ToString();
  }

  std::unique_ptr<Expr> Gen() override;

  std::unique_ptr<Expr> expr_;
};

}  // namespace inter
}  // namespace intellgraph

#endif  // INTELLGRAPH_SRC_PARSER_EXPR_UNARY_H_
