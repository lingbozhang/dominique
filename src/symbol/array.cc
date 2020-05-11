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
#include "src/symbol/array.h"

#include "src/lexer/tag.h"
#include "src/util.h"

namespace intellgraph {
namespace symbols {

Array::Array(std::unique_ptr<Type> type, int size)
    : Type("[]", lexer::tag::kIndex, size * type->width_),
      of_(std::move(type)),
      size_(size) {}
Array::Array(const Array& array)
    : Type("[]", lexer::tag::kIndex, array.size_ * array.of_->width_),
      of_(static_cast_unique_ptr<Type>(array.of_->Clone())),
      size_(array.size_) {}
Array::Array(Array&& array)
    : Type("[]", lexer::tag::kIndex, array.size_ * array.of_->width_),
      of_(std::move(array.of_)),
      size_(std::move(array.size_)) {}
Array& Array::operator=(const Array& array) {
  if (*this != array) {
    Type::operator=(array);
    of_ = static_cast_unique_ptr<Type>(array.of_->Clone());
    size_ = array.size_;
  }
  return *this;
}
Array& Array::operator=(Array&& array) {
  if (*this != array) {
    of_ = std::move(array.of_);
    size_ = array.size_;
    Type::operator=(std::move(array));
  }
  return *this;
}
Array::~Array() = default;

bool Array::operator==(const Array& array) const {
  return Type::operator==(array) && *of_ == *array.of_ && size_ == array.size_;
}

bool Array::operator!=(const Array& array) const { return !(*this == array); }

}  // namespace symbols
}  // namespace intellgraph
