//
//  NetAppCCJSController.h
//  Cocos2dx-js controller
//

#include "GNetApplications.h"

class NetAppCCJSController:public GNetApplications{
private:
    std::vector<std::string> msgList;
    std::map<int,std::string> playerList;
public:
    enum{
        player_name,
        net_data
    }opcode;
    NetAppCCJSController(std::string n):name(n){
        printf("NetAppCCJSController begin\n");
    }
    ~NetAppCCJSController(){
        printf("NetAppCCJSController end\n");
    }
    std::string name;
    void NewConnection(GNPacket gp){
//        pthread_mutex_lock(&mut);
        playerList.insert(std::make_pair(gp.origin, gp.data));
//        pthread_mutex_unlock(&mut);
    }
    void Update(GNPacket gp){
//        pthread_mutex_lock(&mut);
        msgList.push_back(gp.data);
//        pthread_mutex_unlock(&mut);
    }
    void DisConnection(GNPacket){
    
    }
    //启动服务器
    void start_server(int,std::string);
    //启动客户端
    void start_client(std::string);
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

