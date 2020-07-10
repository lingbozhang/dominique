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
#ifndef INTELLGRAPH_SRC_PARSER_EXPR_ACCESS_H_
#define INTELLGRAPH_SRC_PARSER_EXPR_ACCESS_H_

#include "src/parser/expr/id.h"
#include "src/parser/expr/op.h"

namespace intellgraph {
namespace inter {

class Access : public Op {
 public:
   Access(std::unique_ptr<Id> array, std::unique_ptr<Expr> index,
          std::unique_ptr<symbols::Type> type);
   Access(const Access &access);
   Access &operator=(const Access &access);
   ~Access() override;

   bool operator==(const Access &obj) const;
   bool operator!=(const Access &obj) const;

   std::unique_ptr<Expr> Clone() const override {
     return std::make_unique<Access>(*this);
  }

  std::string ToString() const override {
    return array_->ToString() + " [ " + index_->ToString() + " ]";
  }

  std::unique_ptr<Expr> Gen() final;
  void Jumping(int t, int f) final;

  std::unique_ptr<Id> array_;
  std::unique_ptr<Expr> index_;
};

}  // namespace inter
}  // namespace intellgraph

#endif  // INTELLGRAPH_SRC_PARSER_EXPR_ACCESS_H_
