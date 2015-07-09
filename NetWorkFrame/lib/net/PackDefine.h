
#pragma once

#include <string>
#include "ByteBuffer.h"

/////////////////////////////////////////////////////////////////////////
// 数据包
struct GNPacket{
    std::string UUID;
    int code=1;
    std::string NPCode="0";	///< 操作码
    std::string	data="0";
};
//数据包序列化
static ByteBuffer& operator<<(ByteBuffer& lht, const GNPacket& rht){
    lht <<rht.UUID<<rht.code<<rht.NPCode<<rht.data;
    return lht;
};
//数据包反序列化
static ByteBuffer& operator>>(ByteBuffer& lht, GNPacket& rht){
    lht >>rht.UUID>>rht.code>>rht.NPCode>>rht.data;
    return lht;
};
//////////////////////////////////////////////////////////////////////////