load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "stmt",
    srcs = [
        "break.cc",
        "do.cc",
        "else.cc",
        "if.cc",
        "seq.cc",
        "set.cc",
        "set_elem.cc",
        "stmt.cc",
        "while.cc",
    ],
    hdrs = [
        "break.h",
        "do.h",
        "else.h",
        "if.h",
        "seq.h",
        "set.h",
        "set_elem.h",
        "stmt.h",
        "while.h",
    ],
    visibility = ["//visibility:public"],
    deps = [
        "//src/lexer:token",
        "//src/parser:node",
        "//src/parser/expr",
        "//src/symbol",
    ],
)
