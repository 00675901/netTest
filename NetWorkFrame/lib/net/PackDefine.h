
#pragma once

#include <string>
#include "ByteBuffer.h"

//////////////////////////////////////////////////////////////////////////
// 网络数据包
struct NPacket{
    //    unsigned short NPSize;
    int NPCode;	///< 操作码
    std::string	data;
};
//数据包序列化
static ByteBuffer& operator<<(ByteBuffer& lht, const NPacket& rht){
    lht << rht.NPCode<< rht.data;
    return lht;
};
//数据包反序列化
static ByteBuffer& operator>>(ByteBuffer& lht, NPacket& rht){
    lht >> rht.NPCode>> rht.data;
    return lht;
};
//////////////////////////////////////////////////////////////////////////