/* Copyright 2021 The IntellGraph Authors. All Rights Reserved.
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
#include <iostream>
#include <string>

#include "src/lexer/token.h"
#include "src/parser/node.h"
#include "src/symbol/type.h"

using namespace intellgraph;

int main() {
  lexer::Token token('1');
  lexer::Word word("test", '1');
  std::cout << symbols::Type::Int().ToString() << std::endl;
  return 0;
}
