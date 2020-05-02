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
#ifndef INTELLGRAPH_SRC_LEXER_TAG_H_
#define INTELLGRAPH_SRC_LEXER_TAG_H_

namespace intellgraph {
namespace lexer {
namespace tag {

constexpr int kAnd = 256;
constexpr int kBasic = 257;
constexpr int kBreak = 258;
constexpr int kDo = 259;
constexpr int kElse = 260;
constexpr int kEq = 261;
constexpr int kFalse = 262;
constexpr int kGe = 263;
constexpr int kId = 264;
constexpr int kIf = 265;
constexpr int kIndex = 266;
constexpr int kLe = 267;
constexpr int kMinus = 268;
constexpr int kNe = 269;
constexpr int kNum = 270;
constexpr int kOr = 271;
constexpr int kReal = 272;
constexpr int kTemp = 273;
constexpr int kTrue = 274;
constexpr int kWhile = 275;

}  // namespace tag
}  // namespace lexer
}  // namespace intellgraph

#endif  // INTELLGRAPH_SRC_LEXER_TAG_H_
