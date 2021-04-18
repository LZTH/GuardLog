#include "../include/controller.h"


int32_t Controller::Run(const ::google::protobuf::Message& msg) {
    // msg id 和 具体内容分开存储
    // 校验这条消息是否完结flag，若是，则进行持久化, 
    // msg存储进map
    // 对map里的过期数据进行淘汰

    // Uid id = msg.id();

    // int flag = msg.flag();    //flag==1 for complete 

    // if(flag)
    // {
    //     m_DataHandler.complete(id);
    // }

    // else
    // {
    //     m_DataHandler.AddToMap(std::pair<Uid, Message>(id, msg::item))
    // }



    return 0;
}