
#ifndef SVR_UTILS_H_
#define SVR_UTILS_H_

#include <map>
#include <mutex>

namespace svr::utils {

template <typename Key, typename Value>

class ServerThreadSafeMap {
  typedef map<Key, Value>::iterator iter;

 public:
  ServerThreadSafeMap();
  ~ServerThreadSafeMap();

 private:
  map<Key, Value> m_object_;
  std::mutex m_mutexMap;
};

}  // namespace svr::utils

#endif  // SVR_UTILS_H_
