load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")

cc_library(
    name = "token",
    srcs = [
        "token.cc",
    ],
    hdrs = [
        "tag.h",
        "token.h",
    ],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "lexer",
    srcs = [
        "lexer.cc",
    ],
    hdrs = [
        "lexer.h",
    ],
    visibility = ["//visibility:public"],
    deps = [
        ":token",
        "//src/symbol",
    ],
)

cc_test(
    name = "unittests",
    srcs = [
        "lexer_test.cc",
    ],
    copts = ["-Iexternal/gtest/include"],
    deps = [
        ":lexer",
        ":token",
        "@gtest",
        "@gtest//:gtest_main",
    ],
)
