load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")

cc_library(
    name = "symbol",
    srcs = [
        "array.cc",
        "type.cc",
    ],
    hdrs = [
        "array.h",
        "type.h",
    ],
    visibility = ["//visibility:public"],
    deps = [
        "//src:util",
        "//src/lexer:token",
    ],
)

cc_library(
    name = "env",
    srcs = [
        "env.cc",
    ],
    hdrs = ["env.h"],
    visibility = ["//visibility:public"],
    deps = [
        "//src/lexer:token",
        "//src/parser/expr",
    ],
)

cc_test(
    name = "unittests",
    srcs = [
        "array_test.cc",
        "type_test.cc",
    ],
    copts = ["-Iexternal/gtest/include"],
    deps = [
        ":symbol",
        "//src/lexer:token",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)
