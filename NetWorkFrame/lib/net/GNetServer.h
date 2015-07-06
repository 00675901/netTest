//
//  GNetServer.h
//  Cocos2dx
//

#ifndef __TestCocos2dx__GNetServer__
#define __TestCocos2dx__GNetServer__

#include <sys/select.h>
#include <vector>
#include <map>
#include "TcpServer.h"
#include "UdpServer.h"
#include "pthread.h"
#include "PackDefine.h"
#include "GSObserver.h"

//using namespace std;

#define SERVER_STOP 0
#define SERVER_S_RUN 1
#define SERVER_S_PAUSE 2
#define SERVER_C_RUN 3
#define SERVER_C_PAUSE 4
#define SERVER_C_TCP_RUN 5

#define GNOC_GIP ((char *)"si01")
#define GNOC_SIP ((char *)"si02")
#define GNOC_SSNAME ((char *)"sn01")
#define GNOC_SCNAME ((char *)"sn02")

class GNetServer{
private:
    std::map<std::string,GSObserver*> obmap;
    
    //public system member
    UdpServer *udps;
    TcpServer *tcps;
    int serverStatus;
    pthread_mutex_t mut;
    unsigned int localIP;
    int localFD;
    const char* localName;
    std::map<int,unsigned int> remoteFDIP;
    fd_set rfdset;
    ByteBuffer bb;
    
    //UDP Send localIP Service function
    int maxLinsten;
    int localTcpFD;
    pthread_t tidRoomService;
    pthread_t tidListenRoomService;
    
    //UDP search response
    std::map<int, std::string> serverList;
    std::map<int,int> serverListStatus;
    pthread_t tidSearchServer;
    pthread_t tidRecvServer;
    
    //TCP connect
    pthread_t tidConnectService;
    
public:
    GNetServer(void){
        serverStatus=SERVER_STOP;
        pthread_mutex_init(&mut, NULL);
        printf("GNetServer BEGIN\n");
    }
    ~GNetServer(void){
        obmap.clear();
        pthread_mutex_destroy(&mut);
        printf("GNetServer END\n");
    }
    //netService secretary
    void addObs(std::string name ,GSObserver* gob){obmap.insert(std::make_pair(name, gob));}
    void removeObs(std::string name){obmap.erase(name);}
    void notify(std::string name,GNPacket tp){
        obmap[name]->Update(tp);
    }
    void notify(GNPacket tp){
        std::map<std::string,GSObserver*>::iterator iter=obmap.begin();
        while (iter!=obmap.end()) {
            ((*iter).second)->Update(tp);
            iter++;
        }
    }
    
    //use member function
    unsigned int getLocalIP();
    const char* getLocalName();
    std::map<int,unsigned int> getRemoteFDIP();
    
    //UDP Send localIP Service function
    void startResponseService(int maxl,const char* uname);
    void pauseResponseService();
    void resumeResponseService();
    void stopResponseService();
    static void* responseService(void* obj);
    //UDP search response
    void startSearchService();
    void pauseSearchService();
    void resumeSearchService();
    void stopSearchService();
    static void* searchServer(void* obj);
    static void* recvServerList(void* obj);
    //TCP connect
    void startConnectService(int addr);
    void stopConnectService();
    //监听tcp通信
    static void* listenNetService(void* obj);

};

#endif /* defined(__TestCocos2dx__GNetServer__) */
