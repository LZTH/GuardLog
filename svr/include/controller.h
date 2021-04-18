/*
控制整个流程
1. 接收数据，
2. 进行数据预处理
3. 数据筛选
4. 持久化
*/
#ifndef SVR_CONTROLLER_H_
#define SVR_CONTROLLER_H_

#include "data_handler.h"
#include "data_manager.h"
#include "protocal/messages.pb.h"

// <str, str(repeated序列化)>，
// 每次有相同id的消息放入同一个key，序列化后进行存储(serialize), map
// 问题：如何进行过期数据淘汰, map: key: timestamp_id,
// 时间有序，可以淘汰最后的元素, 处理的时候需要加锁,
// 或者是在生成id的时候加上时间戳 持久化暂时先使用文件存储

namespace svr::controller {
class Controller {
 public:
  int32_t Run(const ::google::protobuf::Message& msg);

 private:
  svr::data_handler::DataHandler m_dataHandler;
};
}  // namespace svr::controller

#endif  // SVR_CONTROLLER_H_