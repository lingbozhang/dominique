include(bazel)
cmake_minimum_required(VERSION 3.13)

add_subdirectory(lexer)
add_subdirectory(symbol)
add_subdirectory(parser)

cc_binary(
  NAME "dominique"
  SRCS "main.cc"
  DEPS 
      "parser"
      ${llvm_libs}
)
