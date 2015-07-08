//
//  GApp.h
//  NetWorkFrame
//
//  Created by othink on 15/7/7.
//
//

#include "GNetApplications.h"

class NetApp1:public GNetApplications{
public:
    std::string name;
    
    NetApp1(){
        name="de";
        printf("NetApp1 begin\n");
//        gns=GNetServer::shareInstance();
//        gns->addObs(CLASS_NAME, this);
    }
    ~NetApp1(){
        printf("NetApp1 end\n");
    }
    void Update(GNPacket){
    
    }
    
    void testUpdate(std::string a){
        name=a;
    }
};

