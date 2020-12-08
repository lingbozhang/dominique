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

#include "src/lexer/lexer.h"
#include "src/lexer/token.h"
#include "src/parser/expr/arith.h"
#include "src/parser/expr/constant.h"
#include "src/parser/node.h"
#include "src/parser/parser/parser.h"
#include "src/parser/stmt/set_elem.h"
#include "src/symbol/array.h"
#include "src/symbol/type.h"
#include "llvm/IR/LLVMContext.h"

using namespace intellgraph;

int main(int argc, char *argv[]) {
  int counter;
  printf("Program Name Is: %s", argv[0]);
  if (argc <= 1) {
    printf("Please input codes you want to parse!");
    return 0;
  }
  std::cout << "Input Codes:" << std::endl;
  printf("%s\n", argv[1]);
  std::cout << "Generated three-address intermediate code:" << std::endl;
  auto parser =
      std::make_unique<parser::Parser>(std::make_unique<lexer::Lexer>());
  std::string codes(argv[1]);
  parser->ReadCodes(codes);
  parser->Program();
  return 0;
}
