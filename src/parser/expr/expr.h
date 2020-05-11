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
#ifndef INTELLGRAPH_SRC_PARSER_EXPR_EXPR_H_
#define INTELLGRAPH_SRC_PARSER_EXPR_EXPR_H_

#include <memory>

#include "src/lexer/token.h"
#include "src/parser/node.h"
#include "src/symbol/type.h"

namespace intellgraph {
namespace inter {

class Expr : public Node {
 public:
  Expr(std::unique_ptr<lexer::Token> op, std::unique_ptr<symbols::Type> type);
  Expr(const Expr& expr);
  Expr(Expr&& expr);
  Expr& operator=(const Expr& expr);
  Expr& operator=(Expr&& expr);
  ~Expr() override;

  bool operator==(const Expr& expr) const;
  bool operator!=(const Expr& expr) const;

  virtual std::unique_ptr<Expr> Clone() const {
    return std::make_unique<Expr>(*this);
  }
  virtual std::string ToString() const { return op_->ToString(); }

  virtual std::unique_ptr<Expr> Gen();
  virtual std::unique_ptr<Expr> Reduce();

  virtual void Jumping(int t, int f);
  void EmitJumps(const std::string& test, int t, int f);

  std::unique_ptr<lexer::Token> op_;
  std::unique_ptr<symbols::Type> type_;
};

}  // namespace inter
}  // namespace intellgraph

#endif  // INTELLGRAPH_SRC_PARSER_EXPR_EXPR_H_
