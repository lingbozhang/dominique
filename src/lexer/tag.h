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

inline constexpr int kAnd = 256;
inline constexpr int kBasic = 257;
inline constexpr int kBreak = 258;
inline constexpr int kDo = 259;
inline constexpr int kElse = 260;
inline constexpr int kEq = 261;
inline constexpr int kFalse = 262;
inline constexpr int kGe = 263;
inline constexpr int kId = 264;
inline constexpr int kIf = 265;
inline constexpr int kIndex = 266;
inline constexpr int kLe = 267;
inline constexpr int kMinus = 268;
inline constexpr int kNe = 269;
inline constexpr int kNum = 270;
inline constexpr int kOr = 271;
inline constexpr int kReal = 272;
inline constexpr int kTemp = 273;
inline constexpr int kTrue = 274;
inline constexpr int kWhile = 275;

}  // namespace tag
}  // namespace lexer
}  // namespace intellgraph

#endif  // INTELLGRAPH_SRC_LEXER_TAG_H_
