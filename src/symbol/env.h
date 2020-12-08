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
#ifndef INTELLGRAPH_SRC_SYMBOL_ENV_H_
#define INTELLGRAPH_SRC_SYMBOL_ENV_H_

#include <map>

#include "src/lexer/token.h"
#include "src/parser/expr/id.h"

namespace intellgraph {
namespace symbols {

class Env {
public:
  Env(Env *n);
  ~Env();

  void Put(const lexer::Word &word, std::unique_ptr<inter::Id> id);
  inter::Id *Get(const lexer::Word &word) const;

private:
  std::map<lexer::Word, std::unique_ptr<inter::Id>> word_to_id_;
  Env *prev_ = nullptr;
};

}  // namespace symbols
}  // namespace intellgraph

#endif  // INTELLGRAPH_SRC_SYMBOL_ENV_H_
