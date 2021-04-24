load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "server",
    srcs = [
        "src/controller.cpp",
        "src/data_handler.cpp",
        "src/data_manager.cpp",
    
    ],
    hdrs = [
        "include/controller.h",
        "include/data_handler.h",
        "include/data_manager.h",
    ],
    deps = ['//protocal:message_cc',],
    visibility = ["//visibility:public"],
)
