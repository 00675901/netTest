//
//  GNetApplication.h
//  Cocos2dx
//
#include "PackDefine.h"

class GConInterface{
public:
    GConInterface(void){}
    virtual ~GConInterface(void){}
    
    virtual void Update(GNPacket)=0;
    virtual const char* className()=0;
};

