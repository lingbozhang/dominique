load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")

cc_binary(
    name = "main",
    srcs = ["main.cc"],
    deps = [
        "//src/lexer",
        "//src/parser/parser",
    ],
)

cc_library(
    name = "util",
    hdrs = ["util.h"],
    visibility = ["//visibility:public"],
)
