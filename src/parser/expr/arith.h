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
#ifndef INTELLGRAPH_SRC_PARSER_EXPR_ARITH_H_
#define INTELLGRAPH_SRC_PARSER_EXPR_ARITH_H_

#include "src/parser/expr/expr.h"
#include "src/parser/expr/op.h"
#include "src/symbol/type.h"

namespace intellgraph {
namespace inter {

class Arith : public Op {
 public:
   Arith(std::unique_ptr<lexer::Token> token, std::unique_ptr<Expr> expr1,
         std::unique_ptr<Expr> expr2);
   Arith(const Arith &arith);
   Arith &operator=(const Arith &arith);
   ~Arith() override;

   bool operator==(const Arith &obj) const;
   bool operator!=(const Arith &obj) const;

   std::unique_ptr<Expr> Clone() const override {
     return std::make_unique<Arith>(*this);
   }

  std::string ToString() const override {
    return expr1_->ToString() + " " + this->op_->ToString() + " " +
           expr2_->ToString();
  }

  std::unique_ptr<Expr> Gen() override;

  std::unique_ptr<Expr> expr1_;
  std::unique_ptr<Expr> expr2_;
};

}  // namespace inter
}  // namespace intellgraph

#endif  // INTELLGRAPH_SRC_PARSER_EXPR_ARITH_H_
