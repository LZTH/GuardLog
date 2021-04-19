// 数据处理，包括key timestamp提取，数据清洗，数据压缩
#ifndef SVR_DATA_HANDLER_H_
#define SVR_DATA_HANDLER_H_

#include <cstdint>
#include <cstring>
#include <map>
#include <vector>

#include "svr/include/data_manager.h"
#include "protocal/messages.pb.h"

namespace svr::data_handler {
class DataHandler {
 public:
  bool AddToMap(tutorial::LogData&);  // add to mp
  bool Complete(std::string& id,time_t& timestamp);  // check if it was complete,if so no to add to mp
                              // & clear from mp
  void SaveData(
      int64_t timeStamp);  // check if data in mp was time Err, if so clear

 private:
  // lock

  std::map<std::string, tutorial::ItemList> m_data_;  // to save data
  std::map<time_t, std::vector<std::string>>
      timestamp_to_id_;  // add to find the timeOut data id

  
  svr::data_manager::DataManager m_data_manager_;
};
}  // namespace svr::data_handler
#endif