//
//  GNetApplication.h
//  Cocos2dx
//  libuuid
//  gcc -o uuid uuid.c -luuid
//
#pragma once
#include "GNetServer.h"
#include <uuid/uuid.h>

class GNetApplications:public GNetObserver{
public:
    GNetApplications(){
        gns=GNetServer::shareInstance();
    }
    ~GNetApplications(){}
    std::string UDID;
    GNetServer* gns;
    bool bind(){
        uuid_t uuid;
        char s[40];
        uuid_generate(uuid);
        uuid_unparse_lower(uuid, s);
        std::string keys(s);
        UDID=keys;
        return gns->addObs(UDID, this);
    }
    virtual void Update(GNPacket){}
//    virtual void testUpdate(std::string){}
    void sendMsg(GNPacket msg){
        msg.UUID=this->UDID;
        std::cout<<"UDID="<<this->UDID<<std::endl;
        gns->sendNetPack(msg);
    }
};

