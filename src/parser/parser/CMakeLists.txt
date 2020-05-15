include(bazel)
cmake_minimum_required(VERSION 3.13)

cc_library(
  STATIC
  NAME "parser"
  SRCS "parser.cc"
  HDRS "parser.h"
  DEPS
      "env"
      "expr"
      "gtest"
      "lexer"
      "token"
      "stmt"
      "symbol"
)


cc_test(
  NAME "parser_unittests"
  SRCS "parser_test.cc"
  DEPS "parser"
)
