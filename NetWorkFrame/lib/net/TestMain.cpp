//
//  UDPServer.cpp
//  cocos2dxTest
//

#include "TestMain.h"

#include "NetApp1.h"
#include "NetApp2.h"

//typedef void(*Fun)(std::string,int);

void tmTest(std::string aa,int bb){
    printf("TestMain:\nvalue1:=%s,value2=%d\n",aa.c_str(),bb);
}

void tmTest2(int aa,int bb){
    printf("TestMain2:\nvalue1:=%d,value2=%d\n",aa,bb);
}

void TestMain::begin(){
    NetApp1 *a1=new NetApp1();
    NetApp1 *a2=new NetApp1();
    NetApp2 *b1=new NetApp2();
    NetApp2 *b2=new NetApp2();
        
    std::cout<<(a1->bind("temp1")?"a1 success":"a1 fail")<<std::endl;
    std::cout<<(a2->bind("temp2")?"a2 success":"a2 fail")<<std::endl;
    std::cout<<(b1->bind("temp1")?"b1 success":"b1 fail")<<std::endl;
    std::cout<<(b2->bind("gasdgaegase")?"b2 success":"b2 fail")<<std::endl;
    
    std::cout<<"a1="<<a1->name<<std::endl;
    std::cout<<"a2="<<a2->name<<std::endl;
    std::cout<<"b1="<<b1->name<<std::endl;
    std::cout<<"b2="<<b2->name<<std::endl;
    
    GNetServer *gns=GNetServer::shareInstance();
    gns->testaaaa();
    
    std::cout<<"a1="<<a1->name<<std::endl;
    std::cout<<"a2="<<a2->name<<std::endl;
    std::cout<<"b1="<<b1->name<<std::endl;
    std::cout<<"b2="<<b2->name<<std::endl;

//    std::cout<<CLASS_NAME<<std::endl;
//    std::cout<<a->className()<<std::endl;
//    a.postData("function1",&tmTest);
//    a.postData("function2",&tmTest2);
    
    delete a1;
    delete a2;
    delete b1;
    delete b2;
    
}

