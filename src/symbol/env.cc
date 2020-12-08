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
#include "src/symbol/env.h"

namespace intellgraph {
namespace symbols {

Env::Env(Env* n) : prev_(n) {}

Env::~Env() = default;

void Env::Put(const lexer::Word& word, std::unique_ptr<inter::Id> id) {
  word_to_id_.try_emplace(word, std::move(id));
}

inter::Id* Env::Get(const lexer::Word& word) const {
  const Env* e = this;
  while (e != nullptr) {
    const auto &id_it = e->word_to_id_.find(word);
    if (id_it != e->word_to_id_.end()) {
      return id_it->second.get();
    }
    e = e->prev_;
  }
  return nullptr;
}

}  // namespace symbols
}  // namespace intellgraph
