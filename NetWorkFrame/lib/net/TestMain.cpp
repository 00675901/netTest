//
//  UDPServer.cpp
//  cocos2dxTest
//

#include "TestMain.h"

#include "NetApp1.h"
#include "NetApp2.h"
#include "NetAppCCJSController.h"


//typedef void(*Fun)(std::string,int);

void tmTest(std::string aa,int bb){
    printf("TestMain:\nvalue1:=%s,value2=%d\n",aa.c_str(),bb);
}

void tmTest2(int aa,int bb){
    printf("TestMain2:\nvalue1:=%d,value2=%d\n",aa,bb);
}

void TestMain::begin(){
    NetApp1 *a1=new NetApp1();
    a1->bind();
    NetApp1 *a2=new NetApp1();
    a2->bind();
    
    NetApp2 *b1=new NetApp2();
    b1->bind();
    NetApp2 *b2=new NetApp2();
    b2->bind();
    
    GNPacket msg;

    a1->sendMsg(msg);
    a2->sendMsg(msg);
    b1->sendMsg(msg);
    b2->sendMsg(msg);
    
    delete a1;
    delete a2;
    delete b1;
    delete b2;
////////////////////////////////////////////////////////////////
    
}

