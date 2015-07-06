
#pragma once

#include <string>
#include "ByteBuffer.h"

//////////////////////////////////////////////////////////////////////////
// 数据包
struct GNPacket{
    int code;	//< 操作码
    std::string NPCode;	///< 操作码
    std::string	data;
};
//数据包序列化
static ByteBuffer& operator<<(ByteBuffer& lht, const GNPacket& rht){
    lht <<rht.code<<rht.NPCode<<rht.data;
    return lht;
};
//数据包反序列化
static ByteBuffer& operator>>(ByteBuffer& lht, GNPacket& rht){
    lht >>rht.code>>rht.NPCode>>rht.data;
    return lht;
};
//////////////////////////////////////////////////////////////////////////
