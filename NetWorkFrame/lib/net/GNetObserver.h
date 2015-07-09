//
//  GSObserver.h
//
#include "PackDefine.h"

class GNetObserver{
public:
    GNetObserver(){}
    virtual ~GNetObserver(){}
    virtual void Update(GNPacket)=0;
//    virtual void testUpdate(std::string)=0;
};