// Copyright 2021 tianjunxiong
#include "svr/include/data_handler.h"

#include <algorithm>
#include <cstdint>
#include <ctime>
#include <mutex>
#include <vector>

#include "protocal/messages.pb.h"

namespace svr::data_handler {

std::mutex mtx;

bool DataHandler::AddToMap(const tutorial::LogData& msg) {
  int flag = msg.flag();
  std::string id = msg.id().id();
  time_t timestamp = msg.id().timestamp();
  if (flag) {
    Complete(id, timestamp);
    return true;
  }

  mtx.lock();
  auto data_iter = m_data_.find(id);
  if (data_iter != m_data_.end()) {
    tutorial::Item* item = data_iter->second.add_item_list();
    item->CopyFrom(msg.item());
  } else {
    // save data to m_data_
    tutorial::ItemList item_list;
    tutorial::Item* item = item_list.add_item_list();
    item->CopyFrom(msg.item());
    m_data_.insert(
        std::pair<std::string, tutorial::ItemList>(id, std::move(item_list)));

    // update timestamp index(timestamp map id)
    auto time_iter = timestamp_to_id_.find(timestamp);
    if (time_iter == timestamp_to_id_.end()) {
      std::vector<std::string> id_list;
      id_list.push_back(id);
      timestamp_to_id_.insert(std::pair<time_t, std::vector<std::string>>(
          timestamp, std::move(id_list)));
    } else {
      time_iter->second.push_back(std::move(id));
    }
  }

  mtx.unlock();

  return true;
}

// find id in m_data_ and delete it
// delete id_list in timestamp_to_id_
bool DataHandler::Complete(const std::string& id, time_t timestamp) {
  auto data_iter = m_data_.find(id);
  if (data_iter != m_data_.end()) {
    mtx.lock();
    m_data_.erase(data_iter);
    auto id_list = timestamp_to_id_.find(timestamp);
    // TODO(tianjunxiong): 优化多次erase导致vector内存重新分配的问题
    for (auto id_iter = id_list->second.begin();
         id_iter != id_list->second.end(); ++id_iter) {
      if (*id_iter == id) {
        id_list->second.erase(id_iter);
        break;
      }
    }
  }
  mtx.unlock();
}

return true;
}

void DataHandler::SaveData(time_t timestamp) {
  if (timestamp <= 0) return;
  auto time_iter = timestamp_to_id_.upper_bound(timestamp);

  auto& id_list = timestamp_to_id_[timestamp];
  mtx.lock();

  std::string output;
  for (const auto& id : id_list) {
    auto item_iter = m_data_.find(id);
    if (item_iter != m_data_.end()) {
      output.clear();
      // TODO(tianjunxiong): 处理失败
      if (item_iter->second.SerializeToString(&output)) {
        m_data_manager_.write(output);
      }
      m_data_.erase(item_iter);
    }
  }
  if (time_iter != timestamp_to_id_.end()) timestamp_to_id_.erase(time_iter);

  mtx.unlock();
}
}  // namespace svr::data_handler
