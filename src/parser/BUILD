load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "node",
    srcs = ["node.cc"],
    hdrs = ["node.h"],
    visibility = ["//visibility:public"],
    deps = [
        "//src:util",
        "//src/lexer",
    ],
)
