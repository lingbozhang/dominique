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
#ifndef INTELLGRAPH_SRC_PARSER_STMT_SEQ_H_
#define INTELLGRAPH_SRC_PARSER_STMT_SEQ_H_

#include "src/parser/stmt/stmt.h"

namespace intellgraph {
namespace inter {

class Seq : public Stmt {
 public:
  Seq(std::unique_ptr<Stmt> stmt1, std::unique_ptr<Stmt> stmt2);
  Seq(const Seq& obj);
  Seq& operator=(const Seq& obj);
  ~Seq() override;

  std::unique_ptr<Stmt> Clone() const override {
    return std::make_unique<Seq>(*this);
  }

  void Gen(int b, int a) override;

  std::unique_ptr<Stmt> stmt1_;
  std::unique_ptr<Stmt> stmt2_;
};

}  // namespace inter
}  // namespace intellgraph

#endif  // INTELLGRAPH_SRC_PARSER_STMT_SEQ_H_
