load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")

cc_library(
    name = "parser",
    srcs = ["parser.cc"],
    hdrs = [
        "parser.h",
    ],
    visibility = ["//visibility:public"],
    deps = [
        "//src/lexer",
        "//src/lexer:token",
        "//src/parser/expr",
        "//src/parser/stmt",
        "//src/symbol",
        "//src/symbol:env",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)

cc_test(
    name = "unittests",
    srcs = [
        "parser_test.cc",
    ],
    copts = ["-Iexternal/gtest/include"],
    deps = [
        ":parser",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)
