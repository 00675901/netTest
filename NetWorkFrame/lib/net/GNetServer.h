//
//  GNetServer.h
//  Cocos2dx
//  用于完成基于TCP协议网状结构网络
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
#include "GNetObserver.h"

#define GNOC_GIP ((char *)"si01")
#define GNOC_SIP ((char *)"si02")
#define GNOC_SSNAME ((char *)"sn01")
#define GNOC_SCNAME ((char *)"sn02")

class GNetServer{
private:
    enum{
        SERVER_STOP,
        SERVER_S_RUN,
        SERVER_S_PAUSE,
        SERVER_C_RUN,
        SERVER_C_PAUSE,
        SERVER_C_TCP_RUN
    }serverStatus;
    enum{
        NETNULL,
        GETIP,
        SENDIP
    }NetOPCode;
    
    std::map<std::string,GNetObserver*> obmap;
    
    //public system member
    UdpServer *udps;
    TcpServer *tcps;
//    int serverStatus;
    pthread_mutex_t mut;
    unsigned int localIP;
    int localFD;
    const char* localName;
    //除自己之外,fd-ip表
    std::map<int,unsigned int> remoteFDIP;
    fd_set rfdset;
    ByteBuffer bb;
    
    //UDP Send localIP Service function
    int maxLinsten;
    int localTcpFD;
    pthread_t tidRoomService;
    pthread_t tidListenRoomService;
    
    //UDP search response 用于搜寻网络
    std::map<int, std::string> udpMap; //临时ip-描述信息表
    std::map<int,int> udpMapStatus;
    pthread_t tidSearchServer;
    pthread_t tidRecvServer;
    
    //TCP connect
    pthread_t tidConnectService;
    
    GNetServer(void){
        serverStatus=SERVER_STOP;
        NetOPCode=NETNULL;
        pthread_mutex_init(&mut, NULL);
        printf("GNetServer BEGIN\n");
    }
    ~GNetServer(void){
        obmap.clear();
        pthread_mutex_destroy(&mut);
        printf("GNetServer END\n");
    }
public:
    
    static GNetServer* shareInstance();
    //netService secretary
    bool addObs(std::string name ,GNetObserver* gob){
        if (obmap.find(name)==obmap.end()) {
            obmap.insert(std::make_pair(name, gob));
            return true;
        }
        return false;
    }
    void removeObs(std::string name){obmap.erase(name);}
    void removeAllObs(){obmap.clear();}
    void distributeData(std::string name,GNPacket tp){
        obmap[name]->Update(tp);
    }
    void distributeData(GNPacket tp){
        std::map<std::string,GNetObserver*>::iterator iter=obmap.begin();
        while (iter!=obmap.end()) {
            ((*iter).second)->Update(tp);
            iter++;
        }
    }
    void testaaaa(){
        std::cout<<"---------------------------------------"<<std::endl;
        std::cout<<"obmap size:"<<obmap.size()<<std::endl;
        std::map<std::string,GNetObserver*>::iterator iters;
        for (iters=obmap.begin(); iters!=obmap.end(); ++iters) {
            std::cout<<"key:"<<iters->first<<"---value:"<<iters->second<<std::endl;
            iters->second->testUpdate(iters->first);
        }
        std::cout<<"---------------------------------------"<<std::endl;
    }
    
    //use member function
    unsigned int* getLocalIP();
    const char* getLocalName();
    std::map<int,unsigned int>* getRemoteFDIP(); //获取除自己外fd-ip表
    std::map<int, std::string>* getTempUdpMap();
    
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
    void connectService(int addr);
    void disconnectService();
    //监听tcp通信,接收封包
    static void* listenNetService(void* obj);
    //通过tcp fd 发送封包
    long sendNetPack(int tag,GNPacket);
    long sendNetPack(GNPacket);
};

#endif /* defined(__TestCocos2dx__GNetServer__) */
