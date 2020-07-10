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

int main() {
  auto lex = std::make_unique<lexer::Lexer>();
  auto parser_ = std::make_unique<parser::Parser>(std::move(lex));
  std::string codes = "bool[10] id; id[1] = false;";
  inter::Id expected_id =
      inter::Id(std::make_unique<lexer::Word>("id", lexer::tag::kId),
                std::make_unique<symbols::Array>(
                    symbols::Type::Bool().CloneType(), 10 /* array_size */),
                0 /* offset */);
  inter::Access expected_index = inter::Access(
      std::make_unique<inter::Id>(expected_id),
      std::make_unique<inter::Arith>(
          std::make_unique<lexer::Token>('*'), inter::Constant(1).Clone(),
          std::make_unique<inter::Constant>(1 /* bool_width */)),
      symbols::Type::Bool().CloneType());
  inter::SetElem expected_stmt =
      inter::SetElem(std::make_unique<inter::Access>(expected_index),
                     inter::Constant::False().Clone());
  return 0;
}
