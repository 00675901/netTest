//
//  UDPServer.h
//

#ifndef __cocos2dxTest__UdpServer__
#define __cocos2dxTest__UdpServer__

#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "GUtils.h"

class UdpServer{
private:
    sockaddr_in localAddr;
    sockaddr_in remoteBroAddr;
    sockaddr_in remoteRecAddr;
    bool isBroad;
public:
    int localSo;
    UdpServer(int listenPort,int remotePort,bool isBro);
    ~UdpServer();
    bool iniServer();
    long sendMsg(const char* msg);
    long sendMsg(const char* addr,const char* msg);
    long recvMsg(char* buff,unsigned const int len);
    long recvMsg(char* buff,unsigned const int len,sockaddr_in* remoteRecAD);
};

#endif /* defined(__cocos2dxTest__UdpServer__) */
