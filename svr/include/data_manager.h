// copyright 主要负责存储：cache， 持久化
#ifndef SVR_INCLUDE_DATA_MANAGER_H_
#define SVR_INCLUDE_DATA_MANAGER_H_

#include <string>

namespace svr::data_manager {
class DataManager {
 public:
  virtual bool write(std::string&);
};
}  // namespace svr::data_manager

#endif  // SVR_INCLUDE_DATA_MANAGER_H_
