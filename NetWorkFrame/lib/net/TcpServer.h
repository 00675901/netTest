//
//  TcpServer.h
//  cocos2dxTest
//

#ifndef __cocos2dxTest__TcpServer__
#define __cocos2dxTest__TcpServer__

#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#include "GUtils.h"

class TcpServer{
private:
    int localSo;
    sockaddr_in localAddr;
    sockaddr_in remoteAddr;
public:
    typedef struct{
        std::string opcode;
        std::string data;
    }GCData;
    TcpServer(int listenPort);
    ~TcpServer();
    int iniServer(int instenCount);
    int isAccept();
    int isAccept(sockaddr_in* remoteAD);
    int isConnect(const char* addr,int rematePort);
    int isConnect(int addr,int rematePort);
    
    long sendData(int remoteSo,char* msg);
    long recvData(int remoteSo,char* buffer);
    
    long sendData(int fd,GCData* pack);
    long recvData(int fd,GCData* pack);
};
#endif /* defined(__cocos2dxTest__TcpServer__) */


