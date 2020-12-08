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
#ifndef INTELLGRAPH_SRC_LEXER_LEXER_H_
#define INTELLGRAPH_SRC_LEXER_LEXER_H_

#include <map>
#include <memory>
#include <string>

#include "src/lexer/tag.h"
#include "src/lexer/token.h"

namespace intellgraph {
namespace lexer {

class Lexer {
 public:
   static int get_line_number();

   Lexer();
   Lexer(const Lexer &) = delete;
   Lexer &operator=(const Lexer &) = delete;
   ~Lexer();

   void ReadCodes(const std::string &codes);
   std::unique_ptr<Token> Scan();

 private:
   // Zero initialization
   static int line_num_;

   void Reserve(const std::string &lexeme, std::unique_ptr<Word> wd);
   bool ReadCh();
   bool ReadCh(char c);

   char peek_ = ' ';
   std::string str_;
   std::string::iterator str_iter_;
   std::map<std::string, std::unique_ptr<Word>> words;
};

}  // namespace lexer
}  // namespace intellgraph

#endif  // INTELLGRAPH_SRC_LEXER_LEXER_H_
