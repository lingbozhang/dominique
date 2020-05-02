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
#ifndef INTELLGRAPH_SRC_PARSER_EXPR_LOGICAL_H_
#define INTELLGRAPH_SRC_PARSER_EXPR_LOGICAL_H_

#include "src/parser/expr/expr.h"
#include "src/parser/expr/temp.h"

namespace intellgraph {
namespace inter {

class Logical : public Expr {
 public:
  Logical(std::unique_ptr<lexer::Token> token, std::unique_ptr<Expr> expr1,
          std::unique_ptr<Expr> expr2);
  Logical(const Logical& logical);
  Logical(Logical&& logical);
  Logical& operator=(const Logical& logical);
  Logical& operator=(Logical&& logical);
  ~Logical() override;

  std::unique_ptr<Expr> Clone() const override {
    return std::make_unique<Logical>(*this);
  }

  std::string ToString() const override {
    return expr1_->ToString() + " " + this->op_->ToString() + " " +
           expr2_->ToString();
  }

  std::unique_ptr<Expr> Gen() final;

  virtual std::unique_ptr<symbols::Type> Check(const symbols::Type* type1,
                                               const symbols::Type* type2);

  std::unique_ptr<Expr> expr1_;
  std::unique_ptr<Expr> expr2_;
};

}  // namespace inter
}  // namespace intellgraph

#endif  // INTELLGRAPH_SRC_PARSER_EXPR_LOGICAL_H_