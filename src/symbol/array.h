/* Copyright 2020 The IntellGraph Authors. All Rights Reserved.
Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at
   http://www.apache.org/licenses/LICENSE-2.0
Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

Contributor(s):
        Lingbo Zhang <lingboz2015@gmail.com>
==============================================================================*/
#ifndef INTELLGRAPH_SRC_SYMBOL_ARRAY_H_
#define INTELLGRAPH_SRC_SYMBOL_ARRAY_H_

#include "src/symbol/type.h"

namespace intellgraph {
namespace symbols {

class Array : public Type {
 public:
  Array(std::unique_ptr<Type> type, int size);
  Array(const Array& array);
  Array(Array&& array);
  Array& operator=(const Array& array);
  Array& operator=(Array&& array);
  ~Array() override;

  bool operator==(const Array& array) const;
  bool operator!=(const Array& array) const;

  std::unique_ptr<Token> Clone() const override {
    return std::make_unique<Array>(*this);
  }

  std::unique_ptr<Type> CloneType() const override {
    return std::make_unique<Array>(*this);
  }

  std::string ToString() const override {
    return "[ " + std::to_string(size_) + " ]" + of_->ToString();
  }

  std::unique_ptr<Type> of_;
  int size_;
};

}  // namespace symbols
}  // namespace intellgraph

#endif  // INTELLGRAPH_SRC_SYMBOL_ARRAY_H_
