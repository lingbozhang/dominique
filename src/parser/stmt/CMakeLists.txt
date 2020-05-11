include(bazel)
cmake_minimum_required(VERSION 3.13)

cc_library(
  STATIC
  NAME "stmt"
  SRCS
      "break.cc"
      "do.cc"
      "else.cc"
      "if.cc"
      "seq.cc"
      "set.cc"
      "set_elem.cc"
      "stmt.cc"
      "while.cc"
  HDRS
      "break.h"
      "do.h"
      "else.h"
      "if.h"
      "seq.h"
      "set.h"
      "set_elem.h"
      "stmt.h"
      "while.h"
  PUBLIC_DEPS
      "expr"
      "node"
      "token"
      "symbol"
)
