//
//  GApp.h
//  NetWorkFrame
//
//  Created by othink on 15/7/7.
//
//
#include "GNetApplications.h"

class NetApp2:public GNetApplications{
public:
    std::string name;
    NetApp2(){
        name="de";
        printf("NetApp2 begin\n");
    }
    ~NetApp2(){
        printf("NetApp2 end\n");
    }
    void Update(GNPacket){
    
    }
    
    void testUpdate(std::string a){
        name=a;
    }
};

