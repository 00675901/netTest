//
//  UDPServer.cpp
//  cocos2dxTest
//

#include "TestMain.h"

#include "GSDataPool.h"

//typedef void(*Fun)(std::string,int);

void tmTest(std::string aa,int bb){
    printf("TestMain:\nvalue1:=%s,value2=%d\n",aa.c_str(),bb);
}

void tmTest2(int aa,int bb){
    printf("TestMain2:\nvalue1:=%d,value2=%d\n",aa,bb);
}

void TestMain::begin(){
    GSDataPool a;
//    a.postData("function1",&tmTest);
//    a.postData("function2",&tmTest2);
}

