// Copyright 2021 tianjunxiong
#include "svr/include/data_manager.h"

#include <string.h>

namespace svr::data_manager {
bool DataManager::write(std::string& msg) {
  printf("%s\n", msg.c_str());
  return true;
}
}  // namespace svr::data_manager
