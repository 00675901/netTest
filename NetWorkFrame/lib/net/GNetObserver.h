//
//  GSObserver.h
//
#include "PackDefine.h"

class GNetObserver{
public:
    GNetObserver(){}
    virtual ~GNetObserver(){}
    virtual void distributeData(GNPacket)=0;
};