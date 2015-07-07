//
//  GNetApplication.h
//  Cocos2dx
//
#include "GConInterface.h"

class GConApplications:public GConInterface{
public:
    GConApplications(void){printf("GConApplications begin\n");}
    virtual ~GConApplications(void){}
    
    virtual void Update(GNPacket)=0;
    virtual const char* className()=0;
};

