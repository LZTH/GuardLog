// Copyright 2021 yaozhuang
#include <cstdio>
#include "protocal/messages.pb.h"
#include "svr/include/controller.h"
using svr::controller::Controller;

int main(int argc, char* argv[]) {
  Controller controller;
  tutorial::LogData msg;
  msg.mutable_id()->set_timestamp(time(0));
  msg.mutable_id()->set_id("10086");
  msg.set_flag(1);
  msg.mutable_item()->add_data_list("test");
  int32_t ret = controller.Run(msg);
  if (ret != 0) {
    printf("ERR: controller run ret %d", ret);
    exit(1);
  }
  exit(0);
}