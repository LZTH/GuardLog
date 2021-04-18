
#ifndef UTILS_H_
#define UTILS_H_
#include<map>
#include<mutex>


namespace utils{

template<Key,Value>
class ServerThreadSafeMap
{
    typedef map<Key,Value>::iterator iter;
    public:
        ServerThreadSafeMap();
        ~ServerThreadSafeMap();
        


    private:
        map<Key,Value> m_object_;   
        std::mutex m_mutexMap;     
}








}


#endif