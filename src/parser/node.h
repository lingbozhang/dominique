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
#ifndef INTELLGRAPH_SRC_PARSER_NODE_H_
#define INTELLGRAPH_SRC_PARSER_NODE_H_

#include <iostream>
#include <string>

#include "src/lexer/lexer.h"
#include "src/util.h"

namespace intellgraph {
namespace inter {

class Node {
 public:
  static int labels_;
  static int NewLabel() { return ++labels_; }

  Node();
  virtual ~Node();

  void Error(const std::string& error_message) const {
    std::cout << "near line: " << lex_line_ << ": " << error_message
              << std::endl;
    exit(1);
  }

  void EmitLabel(int i) const { std::cout << "L" << i << ":"; }
  void Emit(const std::string& s) const { PrintLine("\t" + s); }

  int lex_line_ = 0;
};

}  // namespace inter
}  // namespace intellgraph

#endif  // INTELLGRAPH_SRC_PARSER_NODE_H_