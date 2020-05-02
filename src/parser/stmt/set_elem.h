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
#ifndef INTELLGRAPH_SRC_PARSER_STMT_SET_ELEM_H_
#define INTELLGRAPH_SRC_PARSER_STMT_SET_ELEM_H_

#include "src/parser/expr/access.h"
#include "src/parser/expr/expr.h"
#include "src/parser/expr/id.h"
#include "src/parser/stmt/stmt.h"
#include "src/symbol/array.h"

namespace intellgraph {
namespace inter {

class SetElem : public Stmt {
 public:
  SetElem(std::unique_ptr<Access> access, std::unique_ptr<Expr> expr);
  SetElem(const SetElem& obj);
  SetElem(SetElem&& obj);
  SetElem& operator=(const SetElem& obj);
  SetElem& operator=(SetElem&& obj);
  ~SetElem() override;

  std::unique_ptr<Stmt> Clone() const override {
    return std::make_unique<SetElem>(*this);
  }

  std::unique_ptr<symbols::Type> Check(const symbols::Type* type1,
                                       const symbols::Type* type2) const;
  void Gen(int b, int a) override;

  std::unique_ptr<Access> access_;
  std::unique_ptr<Expr> expr_;
};

}  // namespace inter
}  // namespace intellgraph

#endif  // INTELLGRAPH_SRC_PARSER_STMT_SET_ELEM_H_