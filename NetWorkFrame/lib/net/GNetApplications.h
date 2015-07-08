//
//  GNetApplication.h
//  Cocos2dx
//

#include "GNetServer.h"

class GNetApplications:public GNetObserver{
private:
    GNetServer* gns;
public:
    GNetApplications(){
        gns=GNetServer::shareInstance();
    }
    ~GNetApplications(){}
    virtual void Update(GNPacket){}
    virtual void testUpdate(std::string){}
    
    bool bind(std::string key){
        return gns->addObs(key, this);
    }
};

