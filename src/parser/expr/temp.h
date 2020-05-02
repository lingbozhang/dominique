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
#ifndef INTELLGRAPH_SRC_PARSER_EXPR_TEMP_H_
#define INTELLGRAPH_SRC_PARSER_EXPR_TEMP_H_

#include <memory>

#include "src/lexer/token.h"
#include "src/parser/expr/expr.h"
#include "src/symbol/type.h"

namespace intellgraph {
namespace inter {

class Temp : public Expr {
 public:
  static int count_;

  Temp(std::unique_ptr<symbols::Type> type);
  ~Temp() override = default;

  std::unique_ptr<Expr> Clone() const override {
    this->Error("Temp cannot be cloned!");
    return nullptr;
  }

  std::string ToString() const override {
    return "t" + std::to_string(number_);
  }

  int number_ = 0;
};

}  // namespace inter
}  // namespace intellgraph

#endif  // INTLLGRAPH_SRC_PARSER_EXPR_TEMP_H_