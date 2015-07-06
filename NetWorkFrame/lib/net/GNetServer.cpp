//
//  GNetServer.cpp
//  Cocos2dx
//

#include "GNetServer.h"

//use member function
unsigned int GNetServer::getLocalIP(){
    return localIP;
}
const char* GNetServer::getLocalName(){
    return localName;
}
std::map<int,unsigned int> GNetServer::getRemoteFDIP(){
    return remoteFDIP;
}

//Send Room Service function
void GNetServer::startResponseService(int maxl,const char* uname){
    if (SERVER_STOP==serverStatus) {
        serverStatus=SERVER_S_RUN;
        udps=new UdpServer(52156,52157,false);
        if (udps->iniServer()) {
            pthread_create(&tidRoomService,NULL,GNetServer::responseService,this);
            maxLinsten=maxl;
            localName=uname;
            tcps=new TcpServer(52125);
            if ((localTcpFD=tcps->iniServer(maxLinsten))>0) {
                pthread_create(&tidListenRoomService,NULL,GNetServer::listenNetService,this);
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
        long res;
        char tbuffer[8];
        sockaddr_in remoteRecAddr;
        if ((res=temp->recvMsg(tbuffer,8,&remoteRecAddr))>0) {
            const char* sa=inet_ntoa(remoteRecAddr.sin_addr);
            std::string temps=tbuffer;
            const char* s=tis.c_str();
            temp->sendMsg(sa,s);
        }
    }
    return NULL;
}

void* GNetServer::listenNetService(void* obj){
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
    pthread_testcancel();
    GNetServer *temp=(GNetServer *)obj;
    TcpServer *tempTcps=temp->tcps;
    int tempLocalFD=temp->localFD;
    fd_set *temptRfdset=&(temp->rfdset);
    ByteBuffer tempbb=temp->bb;
    std::map<int,unsigned int> *tempRemotaFD=&(temp->remoteFDIP);
    std::string tempLocalName=temp->localName;
    int res;
    int maxFD=0;
    //    struct timeval ov;
    //    ov.tv_sec=1;
    //    ov.tv_usec=0;
    typedef std::pair<int,unsigned int> tp;
    typedef std::pair<int,std::string> ta;
    std::string ts1="a player join the room!";
    std::string ts2="a player leave the room!";
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
        if (sel<0) {
            if (EINTR==errno) {
                continue;
            }else{
                printf("select faild:%m");
            }
        }
        if (FD_ISSET(tempLocalFD, temptRfdset)) {
            sockaddr_in remoteAddr;
            if ((res=tempTcps->isAccept(&remoteAddr))>0) {
                unsigned int reAddr=remoteAddr.sin_addr.s_addr;
                tempRemotaFD->insert(tp(res,reAddr));
            }
        }
        iter=tempRemotaFD->begin();
        while (iter!=tempRemotaFD->end()) {
            if (FD_ISSET(iter->first, temptRfdset)){
                GNPacket tgcd;
                char* pDataBuffer;
                long lenr=tempTcps->recvData(iter->first,pDataBuffer);
                // 清除缓存中数据
                tempbb.clear();
                // 将数据加入到缓存中去
                tempbb.append((uint8_t*)pDataBuffer, sizeof(pDataBuffer));
                tempbb>>tgcd;
                if (lenr<=0) {
                    close(iter->first);
                    tempRemotaFD->erase(iter++);
                }else{
//                    string topc=tgcd.NPCode;
//                    string tdat=tgcd.data;
//                    if (topc.compare(GNOC_SIP)==0) {
//                        int reip=GUtils::ctoi(tdat.c_str());
//                        printf("remota Msg:%s(--%d--)\n",tdat.c_str(),reip);
//                        int tempremo=tempTcps->isConnect(reip, 52125);
//                        if (tempremo>0) {
//                            tempRemotaFD->insert(tp(tempremo,reip));
//                        }
//                    }else if (topc.compare(GNOC_GIP)==0){
//                        map<int,unsigned int>::iterator iters;
//                        for (iters=tempRemotaFD->begin(); iters!=tempRemotaFD->end(); ++iters) {
//                            tgcd.code=0;
//                            tgcd.NPCode=GNOC_SIP;
//                            tgcd.data=iter->second;
//                            tempbb<<tgcd;
//                            tempTcps->sendData(iters->first,(char*)tempbb.contents());
//                        }
//                    }
                    temp->notify(tgcd);
                    iter++;
                }
//                GSNotificationPool::shareInstance()->postNotification("updateRoom", NULL);
//                GSNotificationPool::shareInstance()->postNotification("updateMsg", NULL);
            }else{
                iter++;
            }
        }
    }
    return NULL;
}

void GNetServer::startSearchService(){
    if (SERVER_STOP==serverStatus) {
        serverStatus=SERVER_C_RUN;
        udps=new UdpServer(52157,52156,true);
        if (udps->iniServer()) {
            pthread_create(&tidSearchServer,NULL,GNetServer::searchServer,udps);
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
    std::map<int, int>* temproomlist=&(temp->serverListStatus);
    std::map<int, int>::iterator itm;
    std::map<int, std::string>* temproomlistInfo=&(temp->serverList);
    std::map<int, std::string>::iterator itminfo;
    while (true) {
        pthread_testcancel();
        char s[]="1";
        tempudp->sendMsg(s);
        pthread_mutex_lock(tempmut);
        itm=temproomlist->begin();
        while (itm!=temproomlist->end()) {
            (itm->second)--;
            if (0==itm->second) {
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
    std::map<int, int>* temproomlist=&(tempgr->serverListStatus);
    std::map<int, std::string>* temproomlistInfo=&(tempgr->serverList);
    std::map<int, int>::iterator itm;
    typedef std::pair<int, int> tp;
    typedef std::pair<int, std::string> ts;
    while (true) {
        pthread_testcancel();
        char tbuffer[1024];
        sockaddr_in remoteRecAddr;
        long lenr=tempudps->recvMsg(tbuffer,1024,&remoteRecAddr);
        if (lenr>0) {
            std::string temprip=GUtils::cptos(inet_ntoa(remoteRecAddr.sin_addr));
            int rip=remoteRecAddr.sin_addr.s_addr;
            int liveCount=6;
            pthread_mutex_lock(tempmut);
            itm=temproomlist->find(rip);
            if (itm==temproomlist->end()) {
                temproomlist->insert(tp(rip,liveCount));
                temproomlistInfo->insert(ts(rip,tbuffer));
//                tempgr->notify(tgcd);
//                GSNotificationPool::shareInstance()->postNotification("updateRoomList", NULL);
            }else{
                itm->second=liveCount;
            }
            pthread_mutex_unlock(tempmut);
        }
    }
    return NULL;
}

void GNetServer::startConnectService(int addr){
    if (SERVER_STOP==serverStatus){
        serverStatus=SERVER_C_TCP_RUN;
        tcps=new TcpServer(52125);
        if ((localFD=tcps->iniServer(10))>0) {
            int remoteFD=tcps->isConnect(addr, 52125);
            if (remoteFD>0) {
                pthread_create(&tidConnectService,NULL,GNetServer::listenNetService,this);
                typedef std::pair<int, int> tp;
                remoteFDIP.insert(tp(remoteFD,addr));
                GNPacket msg;
                msg.code=0;
                msg.NPCode=GNOC_GIP;
                msg.data="0";
                bb<<msg;
                tcps->sendData(remoteFD,(char*)bb.contents());
            }
        }
    }
}

void GNetServer::stopConnectService(){
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
