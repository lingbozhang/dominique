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
#ifndef INTELLGRAPH_SRC_PARSER_EXPR_CONSTANT_H_
#define INTELLGRAPH_SRC_PARSER_EXPR_CONSTANT_H_

#include "src/lexer/token.h"
#include "src/parser/expr/expr.h"
#include "src/symbol/type.h"
#include "llvm/IR/LLVMContext.h"

namespace intellgraph {
namespace inter {

class Constant : public Expr {
public:
  static const Constant &True();
  static const Constant &False();

  Constant(std::unique_ptr<lexer::Token> token,
           std::unique_ptr<symbols::Type> type);
  Constant(const Constant &constant);
  Constant &operator=(const Constant &constant);
  Constant(int i);
  ~Constant() override;

  bool operator==(const Constant &constant) const;
  bool operator!=(const Constant &constant) const;

  std::unique_ptr<Expr> Clone() const final {
    return std::make_unique<Constant>(*this);
  }

  void Jumping(int t, int f) override;
};

}  // namespace inter
}  // namespace intellgraph

#endif  // INTELLGRAPH_SRC_PARSE_EXPR_CONSTANT_H_
