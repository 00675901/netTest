
#pragma once

#include <string>
#include "ByteBuffer.h"

////////////////////////////////////////////////////////////GNetServer使用数据包定义开始//////////////////////////////////////////////////////////////////////////////////////
//系统用数据包
//struct GSPacket{
//    int eventCode=-1;    //事件码
//    int tag=0;
//    std::string data="0";
//};
////系统用数据包序列化
//static ByteBuffer& operator<<(ByteBuffer& lht, const GSPacket& rht){
//    lht<<rht.code<<rht.tag<<rht.data;
//    return lht;
//};
////系统用数据包反序列化
//static ByteBuffer& operator>>(ByteBuffer& lht, GSPacket& rht){
//    lht>>rht.code>>rht.tag>>rht.data;
//    return lht;
//};

//数据包
struct GNPacket{
    int sysCode=-1; //系统操作码 小于0:不转发 1:转发
    int origin=-1;
    std::string UUID="0";
    int NPCode=-1;	// 操作码
    std::string	data="0";
};
//数据包序列化
static ByteBuffer& operator<<(ByteBuffer& lht, const GNPacket& rht){
    lht<<rht.sysCode<<rht.origin<<rht.UUID<<rht.NPCode<<rht.data;
    return lht;
};
//数据包反序列化
static ByteBuffer& operator>>(ByteBuffer& lht, GNPacket& rht){
    lht>>rht.sysCode>>rht.origin>>rht.UUID>>rht.NPCode>>rht.data;
    return lht;
};
/////////////////////////////////////////////////////////////GNetServer使用数据包定义结束///////////////////////////////////////////////////////////////////////////////////////