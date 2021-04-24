load("@rules_cc//cc:defs.bzl", "cc_binary")

cc_binary(
    name = "test_run",
    srcs = [
        "test_run.cpp",
    ],
    deps = [
    '//protocal:message_cc',
    '//svr:server',
    ],
    visibility = ["//visibility:public"],
)
