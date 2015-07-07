//
//  GNetApplication.cpp
//  Cocos2dx
//

#include "GNetApplications.h"

void GNetApplications::distributeData(GNPacket){
    
}

void GNetApplications::registerDataContainer(std::string key,std::vector<GNPacket>* list){
    dataMap.insert(std::make_pair(key, list));
}

