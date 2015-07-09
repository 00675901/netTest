//
//  NetAppCCJSController.h
//  Cocos2dx-js controller
//

#include "GNetApplications.h"

class NetAppCCJSController:public GNetApplications{
private:
    std::map<unsigned int,std::string> playerList;
public:
    NetAppCCJSController(){
        printf("NetApp1 begin\n");
    }
    ~NetAppCCJSController(){
        printf("NetApp1 end\n");
    }
    void Update(GNPacket){
        
    }
    //启动服务器
    void start_server(int,std::string);
    //启动客户端
    void start_client();
    //连接服务器
    void connect_server(int ip);
    //获取服务器列表
    std::string get_server_list();
    //获取已经连接到服务器的玩家列表
    std::string get_player_list();
    //发送信息
    bool send_message(std::string jsonString);
    //获取信息
    std::string get_message();
    
};

