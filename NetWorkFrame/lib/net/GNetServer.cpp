//
//  GNetServer.cpp
//  Cocos2dx
//

#include "GNetServer.h"

static GNetServer* GNetServerInstance;
GNetServer* GNetServer::shareInstance(){
    if (!GNetServerInstance) {
        GNetServerInstance=new GNetServer();
    }
    return GNetServerInstance;
}

//use member function
unsigned int* GNetServer::getLocalIP(){
    return &localIP;
}
const char* GNetServer::getLocalName(){
    return localName;
}
std::map<int,unsigned int>* GNetServer::getRemoteFDIP(){
    return &remoteFDIP;
}
std::map<unsigned int, std::string>* GNetServer::getTempUdpMap(){
    return &udpMap;
}

//Send Room Service function
void GNetServer::startResponseService(int maxl,const char* uname){
    if (SERVER_STOP==serverStatus) {
        serverStatus=SERVER_S_RUN;
        udps=new UdpServer(52156,52157,false);
        if (udps->iniServer()) {
//            pthread_create(&tidRoomService,NULL,GNetServer::responseService,this);
            maxLinsten=maxl;
            localName=uname;
            tcps=new TcpServer(52125);
            if ((localTcpFD=tcps->iniServer(maxLinsten))>0) {
                pthread_create(&tidListenRoomService,NULL,GNetServer::listenSNetService,this);
            }
        }
    }
}
void GNetServer::pauseResponseService(){
    if (SERVER_S_RUN==serverStatus) {
        pthread_cancel(tidRoomService);
        serverStatus=SERVER_S_PAUSE;
    }
}
void GNetServer::resumeResponseService(){
    if (SERVER_S_PAUSE==serverStatus) {
        pthread_create(&tidRoomService,NULL,GNetServer::responseService,this);
        serverStatus=SERVER_S_RUN;
    }
}
void GNetServer::stopResponseService(){
    if(SERVER_S_RUN==serverStatus){
        pthread_cancel(tidRoomService);
        pthread_cancel(tidListenRoomService);
        std::map<int,unsigned int>::iterator iter;
        for (iter=remoteFDIP.begin(); iter!=remoteFDIP.end(); ++iter) {
            close(iter->first);
        }
        remoteFDIP.clear();
        delete tcps;
        delete udps;
        serverStatus=SERVER_STOP;
    }
}
void* GNetServer::responseService(void* obj){
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
    GNetServer *tempgr=(GNetServer *)obj;
    UdpServer *temp=tempgr->udps;
    std::string tis=tempgr->localName;
    tis.append("的房间");
    while (true) {
        pthread_testcancel();
        long res=0;
        char tbuffer[8];
        sockaddr_in remoteRecAddr;
        res=temp->recvMsg(tbuffer,8,&remoteRecAddr);
        if (res>0) {
            const char* sa=inet_ntoa(remoteRecAddr.sin_addr);
            std::string temps=tbuffer;
            const char* s=tis.c_str();
            temp->sendMsg(sa,s);
        }
    }
    return NULL;
}

void* GNetServer::listenSNetService(void* obj){
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
    pthread_testcancel();
    GNetServer *temp=(GNetServer *)obj;
    TcpServer *tempTcps=temp->tcps;
    int tempLocalFD=temp->localFD;
    fd_set *temptRfdset=&(temp->rfdset);
    ByteBuffer tempbb=temp->bb;
    std::map<int,unsigned int> *tempRemotaFD=&(temp->remoteFDIP);
    int maxFD=0;
    while (true) {
        pthread_testcancel();
        FD_ZERO(temptRfdset);
        FD_SET(tempLocalFD, temptRfdset);
        maxFD=maxFD>tempLocalFD?maxFD:tempLocalFD;
        std::map<int,unsigned int>::iterator iter;
        for (iter=tempRemotaFD->begin(); iter!=tempRemotaFD->end(); ++iter) {
            FD_SET(iter->first, temptRfdset);
        }
        if (!tempRemotaFD->empty()) {
            --iter;
            maxFD=maxFD>(iter->first)?maxFD:(iter->first);
        }
        int sel=select(maxFD+1, temptRfdset, NULL, NULL, NULL);
        printf("select:%d\n",sel);
        if (sel<0) {
            if (EINTR==errno) {
                continue;
            }else{
                printf("select faild:%m");
            }
        }
        if (FD_ISSET(tempLocalFD, temptRfdset)) {
            sockaddr_in remoteAddr;
            int tempRFD;
            if ((tempRFD=tempTcps->isAccept(&remoteAddr))>0) {
                printf("有人连接了\n");
                unsigned int reAddr=remoteAddr.sin_addr.s_addr;
                tempRemotaFD->insert(std::make_pair(tempRFD,reAddr));
                for (iter=tempRemotaFD->begin();iter!=tempRemotaFD->end(); ++iter) {
                    std::cout<<"ip:"<<iter->second<<std::endl;
//                    GNPacket tgcd;
//                    tgcd.sysCode=SEND_IP;
//                    tgcd.data=iter->second;
//                    tempbb.clear();
//                    tempbb<<tgcd;
//                    tempTcps->sendData(tempRFD,(char*)tempbb.contents());
                    char aa[]="this Server";
                    tempTcps->sendData(tempRFD,aa);
                }
//                tempRemotaFD->insert(std::make_pair(tempRFD,reAddr));
            }
        }
        iter=tempRemotaFD->begin();
        while (iter!=tempRemotaFD->end()) {
            if (FD_ISSET(iter->first, temptRfdset)){
                char pDataBuffer[1024];
                long lenr=tempTcps->recvData(iter->first,pDataBuffer);
                printf("服务器接收到一个数据包:%ld\n",lenr);
                iter++;
//                if (lenr<=0) {
//                    close(iter->first);
//                    tempRemotaFD->erase(iter++);
//                    //系统通知有连接断开
//                    GNPacket smsg;
//                    smsg.sysCode=DISCONNECTION;
//                    smsg.origin=iter->first;
//                    temp->notificationSystemData(smsg);
//                }else{
//                    GNPacket tgcd;
//                    // 清除缓存中数据
//                    tempbb.clear();
//                    // 将数据加入到缓存中去
//                    tempbb.append((uint8_t*)pDataBuffer, sizeof(pDataBuffer));
//                    tempbb>>tgcd;
//                    iter++;
//                    int tcd=tgcd.sysCode;
//                    if (PLAYER_NAME==tcd) {
//                        std::string tempn(temp->getLocalName());
//                        GNPacket msg;
//                        msg.sysCode=REPLAYER_NAME;
//                        msg.data=tempn;
//                        tempbb.clear();
//                        tempbb<<msg;
//                        if (tempTcps->sendData(iter->first,(char*)tempbb.contents())>0) {
//                            //系统通知有新连接
//                            GNPacket smsg;
//                            smsg.sysCode=NEWCONNECTION;
//                            smsg.origin=iter->first;
//                            smsg.data=tgcd.data;
//                            temp->notificationSystemData(smsg);
//                        }
//                    }else{
//                        temp->distributeData(tgcd.UUID,tgcd);
//                    }
//                }
            }else{
                iter++;
            }
        }
    }
    return NULL;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GNetServer::startSearchService(const char* uname){
    if (SERVER_STOP==serverStatus) {
        serverStatus=SERVER_C_RUN;
        localName=uname;
        udps=new UdpServer(52157,52156,true);
        if (udps->iniServer()) {
            pthread_create(&tidSearchServer,NULL,GNetServer::searchServer,this);
            pthread_create(&tidRecvServer,NULL,GNetServer::recvServerList,this);
        }
    }
}
void GNetServer::pauseSearchService(){
    if (SERVER_C_RUN==serverStatus) {
        serverStatus=SERVER_C_PAUSE;
        pthread_cancel(tidSearchServer);
        pthread_cancel(tidRecvServer);
    }
}
void GNetServer::resumeSearchService(){
    if (SERVER_C_PAUSE==serverStatus) {
        serverStatus=SERVER_C_RUN;
        pthread_create(&tidSearchServer,NULL,GNetServer::searchServer,this);
        pthread_create(&tidRecvServer,NULL,GNetServer::recvServerList,this);
    }
}
void GNetServer::stopSearchService(){
    if (SERVER_C_RUN==serverStatus) {
        pthread_cancel(tidSearchServer);
        pthread_cancel(tidRecvServer);
        delete udps;
        serverStatus=SERVER_STOP;
    }
}
void* GNetServer::searchServer(void* obj){
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
    GNetServer *temp=(GNetServer *)obj;
    UdpServer* tempudp=temp->udps;
    pthread_mutex_t* tempmut=&(temp->mut);
    std::map<int, int>* temproomlist=&(temp->udpMapStatus);
    std::map<int, int>::iterator itm;
    std::map<unsigned int, std::string>* temproomlistInfo=&(temp->udpMap);
    std::map<unsigned int, std::string>::iterator itminfo;
    while (true) {
        pthread_testcancel();
        char s='1';
        tempudp->sendMsg(&s);
        pthread_mutex_lock(tempmut);
        itm=temproomlist->begin();
        while (itm!=temproomlist->end()) {
            (itm->second)--;
            if (itm->second<=0) {
                std::cout<<"room:"<<itm->first<<" closed"<<std::endl;
                itminfo=temproomlistInfo->find(itm->first);
                temproomlistInfo->erase(itminfo);
                temproomlist->erase(itm++);
            }else{
                itm++;
            }
        }
        pthread_mutex_unlock(tempmut);
        sleep(1);
    }
    return NULL;
}
void* GNetServer::recvServerList(void* obj){
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
    pthread_testcancel();
    GNetServer* tempgr=(GNetServer*)obj;
    UdpServer* tempudps=tempgr->udps;
    pthread_mutex_t* tempmut=&(tempgr->mut);
    std::map<unsigned int, std::string>* temproomlistInfo=&(tempgr->udpMap);
    std::map<int, int>* temproomlist=&(tempgr->udpMapStatus);
    std::map<int, int>::iterator itm;
    while (true) {
        pthread_testcancel();
        char tbuffer[1024];
        sockaddr_in remoteRecAddr;
        long lenr=tempudps->recvMsg(tbuffer,1024,&remoteRecAddr);
        printf("接收UDP数据：%ld\n",lenr);
        if (lenr>0) {
            std::string temprip=GUtils::cptos(inet_ntoa(remoteRecAddr.sin_addr));
            int rip=remoteRecAddr.sin_addr.s_addr;
            pthread_mutex_lock(tempmut);
            itm=temproomlist->find(rip);
            if (itm==temproomlist->end()) {
                temproomlist->insert(std::make_pair(rip,UDPLIVECOUNT));
                temproomlistInfo->insert(std::make_pair(rip,tbuffer));
                //搜索到一个UDP信号
            }else{
                itm->second=UDPLIVECOUNT;
            }
            pthread_mutex_unlock(tempmut);
        }
    }
    return NULL;
}

void GNetServer::connectService(int addr){
    if (SERVER_C_TCP_RUN!=serverStatus){
        serverStatus=SERVER_C_TCP_RUN;
        tcps=new TcpServer(52125);
        if ((localFD=tcps->iniServer(10))>0) {
            int remoteFD=tcps->isConnect(addr, 52125);
            if (remoteFD>0) {
                printf("GNetServer:连接成功\n");
                pthread_create(&tidConnectService,NULL,GNetServer::listenCNetService,this);
                remoteFDIP.insert(std::make_pair(remoteFD,addr));
                std::string tempn(getLocalName());
                ByteBuffer bbs;
                GNPacket msg;
                msg.sysCode=PLAYER_NAME;
                msg.data=tempn;
                bbs<<msg;
                std::cout<<"content size:"<<bbs.size()<<std::endl;
                std::cout<<"content:"<<bbs.contents()<<std::endl;
                char content[]="testtest";
                
                tcps->sendData(remoteFD,content);
//                tcps->sendData(remoteFD,(char*)bbs.contents());
            }else{
                printf("GNetServer:连接失败（%d）\n",remoteFD);
            }
        }
    }
}

void* GNetServer::listenCNetService(void* obj){
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
    pthread_testcancel();
    GNetServer *temp=(GNetServer *)obj;
    TcpServer *tempTcps=temp->tcps;
    int tempLocalFD=temp->localFD;
    fd_set *temptRfdset=&(temp->rfdset);
    ByteBuffer tempbb=temp->bb;
    std::map<int,unsigned int> *tempRemotaFD=&(temp->remoteFDIP);
    while (true) {
        pthread_testcancel();
        FD_ZERO(temptRfdset);
        FD_SET(tempLocalFD, temptRfdset);
        int maxFD=0;
        maxFD=maxFD>tempLocalFD?maxFD:tempLocalFD;
        std::map<int,unsigned int>::iterator iter;
        for (iter=tempRemotaFD->begin(); iter!=tempRemotaFD->end(); ++iter) {
            FD_SET(iter->first, temptRfdset);
        }
        if (!tempRemotaFD->empty()) {
            --iter;
            maxFD=maxFD>(iter->first)?maxFD:(iter->first);
        }
        int sel=select(maxFD+1, temptRfdset, NULL, NULL, NULL);
        printf("select:%d\n",sel);
        if (sel<0) {
            if (EINTR==errno) {
                continue;
            }else{
                printf("select faild:%m");
            }
        }
        if (FD_ISSET(tempLocalFD, temptRfdset)) {
            sockaddr_in remoteAddr;
            int tempRFD;
            if ((tempRFD=tempTcps->isAccept(&remoteAddr))>0) {
                unsigned int reAddr=remoteAddr.sin_addr.s_addr;
                tempRemotaFD->insert(std::make_pair(tempRFD,reAddr));
            }
        }
        
        iter=tempRemotaFD->begin();
        while (iter!=tempRemotaFD->end()) {
            if (FD_ISSET(iter->first, temptRfdset)){
                char pDataBuffer[1024];
                long lenr=tempTcps->recvData(iter->first,pDataBuffer);
                printf("Client Recv:%s(%ld)\n",pDataBuffer,lenr);
                iter++;
                sleep(1);
//                if (lenr<=0) {
//                    close(iter->first);
//                    tempRemotaFD->erase(iter++);
//                    //系统通知有连接断开
//                    GNPacket smsg;
//                    smsg.sysCode=DISCONNECTION;
//                    smsg.origin=iter->first;
//                    temp->notificationSystemData(smsg);
//                }else{
//                    GNPacket tgcd;
//                    // 清除缓存中数据
//                    tempbb.clear();
//                    // 将数据加入到缓存中去
//                    tempbb.append((uint8_t*)pDataBuffer, sizeof(pDataBuffer));
//                    tempbb>>tgcd;
//                    int tcd=tgcd.sysCode;
//                    if (SEND_IP==tcd) {
//                        int reip=GUtils::ctoi((tgcd.data).c_str());
//                        printf("remota Msg:%s(--%d--)\n",(tgcd.data).c_str(),reip);
//                        int tempremo=tempTcps->isConnect(reip, 52125);
//                        if (tempremo>0) {
//                            tempRemotaFD->insert(std::make_pair(tempremo,reip));
//                            std::string tempn(temp->getLocalName());
//                            GNPacket msg;
//                            msg.sysCode=PLAYER_NAME;
//                            msg.data=tempn;
//                            tempbb.clear();
//                            tempbb<<msg;
//                            tempTcps->sendData(tempremo,(char*)tempbb.contents());
//                        }
//                    }else if (REPLAYER_NAME==tcd) {
//                        //系统通知有新连接
//                        GNPacket smsg;
//                        smsg.sysCode=NEWCONNECTION;
//                        smsg.origin=iter->first;
//                        smsg.data=tgcd.data;
//                        temp->notificationSystemData(smsg);
//                    }else if (PLAYER_NAME==tcd) {
//                        std::string tempn(temp->getLocalName());
//                        GNPacket msg;
//                        msg.sysCode=REPLAYER_NAME;
//                        msg.data=tempn;
//                        tempbb.clear();
//                        tempbb<<msg;
//                        if (tempTcps->sendData(iter->first,(char*)tempbb.contents())>0) {
//                            //系统通知有新连接
//                            GNPacket smsg;
//                            smsg.sysCode=NEWCONNECTION;
//                            smsg.origin=iter->first;
//                            smsg.data=tgcd.data;
//                            temp->notificationSystemData(smsg);
//                        }
//                    }else{
//                        temp->distributeData(tgcd.UUID,tgcd);
//                    }
//                    iter++;
//                }
            }else{
                iter++;
            }
        }
    }
    return NULL;
}

long GNetServer::sendNetPack(int fd,GNPacket np){
    GNPacket msg;
    bb<<msg;
    return tcps->sendData(fd,(char*)bb.contents());
}
long GNetServer::sendNetPack(GNPacket np){
    long i=0;
    std::map<int,unsigned int>::iterator iter;
    for (iter=remoteFDIP.begin(); iter!=remoteFDIP.end(); ++iter) {
        i+=sendNetPack(iter->first, np);
    }
    return i;
}

void GNetServer::disconnectService(){
    if (SERVER_C_TCP_RUN==serverStatus){
        pthread_cancel(tidConnectService);
        std::map<int,unsigned int>::iterator iter;
        for (iter=remoteFDIP.begin(); iter!=remoteFDIP.end(); ++iter) {
            close(iter->first);
        }
        remoteFDIP.clear();
        close(localFD);
        delete tcps;
        serverStatus=SERVER_STOP;
    }
}
