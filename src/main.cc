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

#include "src/lexer/lexer.h"
#include "src/parser/parser/parser.h"

int main() {
  std::string codes =
      "{\n"
      "int[100] x; int y;\n"
      "y = x[1];\n"
      "}";
  auto lex = std::make_unique<intellgraph::lexer::Lexer>();
  auto parser = std::make_unique<intellgraph::parser::Parser>(std::move(lex));
  parser->ReadCodes(codes);
  parser->Program();
  return 0;
}
