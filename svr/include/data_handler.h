// Copyright 2021 tianjunxiong
#ifndef SVR_INCLUDE_DATA_HANDLER_H_
#define SVR_INCLUDE_DATA_HANDLER_H_

#include <cstdint>
#include <ctime>
#include <map>
#include <string>
#include <vector>
#include "protocal/messages.pb.h"
#include "svr/include/data_manager.h"

namespace svr::data_handler {
class DataHandler {
 public:
  bool AddToMap(const tutorial::LogData &);
  bool Complete(const std::string &id, const time_t timestamp);
  void SaveData(time_t timeStamp);

 private:
  std::map<std::string, tutorial::ItemList> m_data_;
  std::map<time_t, std::vector<std::string>> timestamp_to_id_;
  svr::data_manager::DataManager m_data_manager_;
};
}  // namespace svr::data_handler
#endif  // SVR_INCLUDE_DATA_HANDLER_H_
