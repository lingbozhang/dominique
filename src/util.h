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
#ifndef INTELLGRAPH_SRC_UTIL_H_
#define INTELLGRAPH_SRC_UTIL_H_

#include <ctype.h>
#include <stdlib.h>

#include <iostream>
#include <sstream>

namespace intellgraph {

template <typename D, typename B>
std::unique_ptr<D> static_cast_unique_ptr(std::unique_ptr<B> base) {
  return std::unique_ptr<D>(static_cast<D*>(base.release()));
}

inline void PrintLine(const std::string& str) { std::cout << str << std::endl; }

}  // namespace intellgraph

#endif  // INTELLGRAPH_SRC_UTIL_H_
