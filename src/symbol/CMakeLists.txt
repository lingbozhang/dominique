include(bazel)
cmake_minimum_required(VERSION 3.8)

cc_library(
  STATIC
  NAME "symbol"
  SRCS
      "array.cc"
      "type.cc"
  HDRS
      "array.h"
      "type.h"
  PUBLIC_DEPS 
      "token"
      ${llvm_libs}
)
 
cc_library(
  NAME "env"
  SRCS "env.cc"
  HDRS "env.h"
  PUBLIC_DEPS
      "expr"
      "token"
)

cc_test(
  NAME "symbol_unittests"
  SRCS 
      "array_test.cc"
      "type_test.cc"
  DEPS
      "token"
      "symbol"
)
