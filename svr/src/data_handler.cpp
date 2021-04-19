#include "svr/include/data_handler.h"

#include <cstdint>
#include <mutex>
#include <vector>
#include<ctime>
#include<algorithm>

#include "protocal/messages.pb.h"

namespace svr::data_handler {

std::mutex mtx;

bool DataHandler::AddToMap(tutorial::LogData& msg) {
  int flag = msg.flag();
  std::string id = msg.id().id();
  time_t timestamp = msg.id().timestamp();

  if (flag) {
    Complete(id,timestamp);
    return true;
  }
  mtx.lock();
  auto iter = m_data_.find(id);
  if (iter != m_data_.end()) {
    tutorial::Item* item = m_data_[id].add_item_list();
    *item = msg.item();
  } else {
    tutorial::ItemList item_list;
    tutorial::Item* item = item_list.add_item_list();
    *item = msg.item();
    m_data_.insert(
        std::pair<std::string, tutorial::ItemList>(id, item_list));

    auto time_iter = timestamp_to_id_.find(timestamp);
    if(time_iter==timestamp_to_id_.end()){
      std::vector<std::string> id_list;
      id_list.push_back(id);
      timestamp_to_id_.insert(std::pair<time_t, std::vector<std::string>>(timestamp, id_list));
    }else{
      timestamp_to_id_[timestamp].push_back(id);
    }
  }
  mtx.unlock();

  return true;
}

bool DataHandler::Complete(std::string& id, time_t& timestamp) {
  auto iter = m_data_.find(id);
  if (iter != m_data_.end()) {
    mtx.lock();
    m_data_.erase(iter);

    auto id_list = timestamp_to_id_.at(timestamp);
    for(auto iter = id_list.begin(); iter != id_list.end(); ++iter){
      if(*iter == id)
      id_list.erase(iter);
      break;
    }

    mtx.unlock();
    return true;
  }
  return false;
}

void DataHandler::SaveData(time_t timestamp) {
  if(timestamp <= 0)return ;
  auto time_iter = timestamp_to_id_.upper_bound(timestamp);

    std::vector<std::string> id_list = timestamp_to_id_[timestamp];
    mtx.lock();

    for(auto id_iter:id_list){
      auto item_iter = m_data_.find(id_iter);
      if(item_iter != m_data_.end())
      {
        std::string output;
        m_data_[id_iter].SerializeToString(&output);
        m_data_manager_.write(output);
        m_data_.erase(item_iter);
      }
   }
   timestamp_to_id_.erase(time_iter);

  mtx.unlock();
}

}  // namespace svr::data_handler
