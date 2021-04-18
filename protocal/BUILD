# load("@rules_cc//cc:defs.bzl", "cc_proto_library","cc_library")
load("@rules_proto//proto:defs.bzl", "proto_library")
load("@com_google_protobuf//:protobuf_deps.bzl", "protobuf_deps")
package(default_visibility = ["//visibility:public"])


proto_library(
    name = 'messages_proto',
    srcs = ['messages.proto',],
)

cc_proto_library(
    name = 'message_cc_proto',
    deps = [
        ':messages_proto',
    ],
)

cc_library(
    name = 'message_cc',
    deps = [
        ':message_cc_proto',
    ],
)