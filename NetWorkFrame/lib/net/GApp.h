//
//  GApp.h
//  NetWorkFrame
//
//  Created by othink on 15/7/7.
//
//
#include "GConApplications.h"

class GApp:public GConApplications{
public:
    GApp(){printf("GApp begin\n");}
    ~GApp(){}
    void Update(GNPacket){
    
    }
    const char* className(){
        return typeid(this).name();
    }
};

