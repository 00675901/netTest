//
//  GSObserver.h
//
#include "PackDefine.h"

#define CLASS_NAME typeid(this).name()
class GNetObserver{
public:
    GNetObserver(){}
    virtual ~GNetObserver(){}
    virtual void Update(GNPacket)=0;
    virtual void testUpdate(std::string)=0;
};