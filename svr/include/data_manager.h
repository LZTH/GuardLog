// 主要负责存储：cache， 持久化
#ifndef DATA_MANAGER_H_
#define DATA_MANAGER_H_
#include<string>
class DataManager
{
    public :
        virtual bool write(std::string&);
    
};

#endif