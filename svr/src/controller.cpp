// Copyright 2021 tianjunxiong
#include "svr/include/controller.h"

#include <google/protobuf/message.h>
#define TIME_OUT 10

namespace svr::controller {
int32_t Controller::Run(const tutorial::LogData &msg) {
  // msg id 和 具体内容分开存储
  // 校验这条消息是否完结flag，若是，则进行持久化,
  // msg存储进map
  // 对map里的过期数据进行淘汰
  m_data_handler_.AddToMap(msg);

  m_data_handler_.SaveData(msg.id().timestamp() - TIME_OUT);

  return 0;
}
}  // namespace svr::controller
