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
#ifndef INTELLGRAPH_SRC_PARSER_EXPR_AND_H_
#define INTELLGRAPH_SRC_PARSER_EXPR_AND_H_

#include "src/lexer/token.h"
#include "src/parser/expr/expr.h"
#include "src/parser/expr/logical.h"

namespace intellgraph {
namespace inter {

class And : public Logical {
public:
  And(std::unique_ptr<lexer::Token> token, std::unique_ptr<Expr> expr1,
      std::unique_ptr<Expr> expr2);
  And(const And &obj);
  And &operator=(const And &obj);
  ~And() override;

  std::unique_ptr<Expr> Clone() const override {
    return std::make_unique<And>(*this);
  }

  void Jumping(int t, int f) final;
  std::unique_ptr<symbols::Type> Check(const symbols::Type *type1,
                                       const symbols::Type *type2) override;
};

}  // namespace inter
}  // namespace intellgraph

#endif  // INTELLGRAPH_SRC_PARSER_EXPR_AND_H_
