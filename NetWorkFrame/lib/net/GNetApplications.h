//
//  GNetApplication.h
//  Cocos2dx
//

#include "GNetServer.h"

class GNetApplications{
private:
    std::map<std::string,std::vector<GNPacket>*> dataMap;
public:
    GNetApplications(void){}
    virtual ~GNetApplications(void){}
    virtual void Update(GNPacket);
    void registerDataContainer(std::string,std::vector<GNPacket>*);
};

