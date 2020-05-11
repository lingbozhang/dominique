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
      "lexer"
      "token"
      "stmt"
      "symbol"
)
