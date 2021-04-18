#include "../include/data_handler.h"
#include<mutex>

std::mutex mtx;

bool DataHandler::AddToMap(tutorial::Message& msg)
{
    int flag = msg.flag();
    int64_t id = msg.id().id();

    if(flag)
    {
        Complete(id);
        return true;
    }

    auto iter = m_data_.find(id);
    if(iter != m_data_.end())
    {
        auto item = msg.item();
        m_data_[id].push_back(item);
    }
    else
    {
        mtx.lock();
        std::vector<tutorial::Item> item_list;
        item_list.push_back(msg.item());
        m_data_.insert(std::pair<int64_t, std::vector<tutorial::Item>>(id, item_list));
        mtx.unlock();
    }

    return true;
}

bool DataHandler::Complete(int64_t id)   
{
    auto iter = m_data_.find(id);
    if(iter != m_data_.end())
    {
        mtx.lock();
        m_data_.erase(iter);
        mtx.unlock();
        return true;
    }
    return false;
}

void DataHandler::ClearData(int64_t timeStamp)
{
    
}