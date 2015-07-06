//
//  GNetApplication.cpp
//  Cocos2dx
//

#include "GNetApplications.h"

void GNetApplications::registerDataContainer(std::string key,std::vector<GNPacket>* list){
    dataMap.insert(std::make_pair(key, list));
}

void GNetApplications::Update(GNPacket a){
    printf("code=%d,NOPCode=%s,data=%s",a.code,a.NPCode.c_str(),a.data.c_str());
}