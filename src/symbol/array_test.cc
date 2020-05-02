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

#include "gtest/gtest.h"

namespace intellgraph {
namespace symbols {

TEST(ArrayTest, Equality) {
  Array array1(Type::Float().CloneType(), 1);
  Array array2(Type::Float().CloneType(), 1);
  Array array3(Type::Int().CloneType(), 1);
  EXPECT_TRUE(array1 == array2);
  EXPECT_TRUE(array1 != array3);
}

TEST(ArrayTest, MoveAssignment) {
  Array array1(Type::Float().CloneType(), 1);
  Array array2 = Array(Type::Float().CloneType(), 1);
  EXPECT_EQ(array1, array2);
}

TEST(ArrayTest, CopyAssignment) {
  Array array1(Type::Float().CloneType(), 1);
  Array array2 = array1;
  EXPECT_EQ(array1, array2);
}

}  // namespace symbols
}  // namespace intellgraph