// 数据处理，包括key timestamp提取，数据清洗，数据压缩
#ifndef _DATA_HANDLER_H_
#define _DATA_HANDLER_H_

#include<cstring>
#include<map>
#include<vector>
#include "../include/data_manager.h"
#include "protocal/messages.pb.h"

class DataHandler 
{
    public:
        bool AddToMap(tutorial::Message&);                  //add to mp
        bool Complete(int64_t id);                               //check if it was complete,if so no to add to mp & clear from mp
        void ClearData(int64_t timeStamp);                         //check if data in mp was time Err, if so clear
        
    private:

    // lock

        std::map<int64_t, std::vector<tutorial::Item>> m_data_;           //to save data
        std::map<int64_t, std::vector<int64_t>> timestamp_to_id_;             //add to find the timeOut data id


        // 
        DataManager m_data_manager_;
};
#endif