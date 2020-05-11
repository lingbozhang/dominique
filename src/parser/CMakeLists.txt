include(bazel)
cmake_minimum_required(VERSION 3.13)

add_subdirectory(expr)
add_subdirectory(stmt)
add_subdirectory(parser)

cc_library(
  STATIC
  NAME "node"
  SRCS "node.cc"
  HDRS "node.h"
  DEPS "lexer"
)
