//
//  GNetApplication.h
//  Cocos2dx
//

#include "GNetServer.h"
#include "GConInterface.h"

class GNetApplications:public GNetObserver{
private:
    std::map<std::string,std::vector<GNPacket>*> dataMap;
    std::map<std::string,GConInterface*> controllerMap;
public:
    GNetApplications(void){}
    virtual ~GNetApplications(void){}
    void distributeData(GNPacket);
    void registerDataContainer(std::string,std::vector<GNPacket>*);
};

