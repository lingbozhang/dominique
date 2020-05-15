include(bazel)
cmake_minimum_required(VERSION 3.13)

cc_library(
  STATIC
  NAME "token"
  SRCS "token.cc"
  HDRS
      "tag.h"
      "token.h"
)

cc_library(
  STATIC
  NAME "lexer"
  SRCS "lexer.cc"
  HDRS "lexer.h"
  DEPS "symbol"
)

cc_test(
  NAME "lexer_unittests"
  SRCS "lexer_test.cc"
  DEPS
      "lexer"
      "token"
)
