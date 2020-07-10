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
#ifndef INTELLGRAPH_SRC_PARSER_EXPR_ID_H_
#define INTELLGRAPH_SRC_PARSER_EXPR_ID_H_

#include "src/lexer/token.h"
#include "src/parser/expr/expr.h"
#include "src/symbol/type.h"

namespace intellgraph {
namespace inter {

class Id : public Expr {
 public:
   Id(std::unique_ptr<lexer::Word> token, std::unique_ptr<symbols::Type> type,
      int offset);
   Id(const Id &id);
   Id &operator=(const Id &id);
   ~Id() override;

   bool operator==(const Id &id) const;
   bool operator!=(const Id &id) const;

   std::unique_ptr<Expr> Clone() const final {
     return std::make_unique<Id>(*this);
  }

  std::unique_ptr<Id> CloneId() const { return std::make_unique<Id>(*this); }
  // Relative address of the identifier
  int offset_;
};

}  // namespace inter
}  // namespace intellgraph

#endif  // INTELLGRAPH_SRC_PARSER_EXPR_ID_H_
