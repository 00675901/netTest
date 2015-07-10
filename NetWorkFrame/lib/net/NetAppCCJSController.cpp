//
//  GApp.h
//  NetWorkFrame
//
//  Created by othink on 15/7/7.
//
//
#include "NetAppCCJSController.h"
//启动服务器
void NetAppCCJSController::start_server(int playerCount,std::string serverName){
    gns->startResponseService(playerCount, serverName.c_str());
}
//启动客户端
void NetAppCCJSController::start_client(std::string clientName){
    gns->startSearchService(clientName.c_str());
}
//连接服务器
void NetAppCCJSController::connect_server(int ip){
    gns->connectService(ip);
}
std::string NetAppCCJSController::get_server_list(){
    gns->getTempUdpMap();
    return "";
}
//获取已经连接到服务器的玩家列表
std::string NetAppCCJSController::get_player_list(){
//    playerList;
    return "";
};
//发送信息
bool NetAppCCJSController::send_message(std::string jsonString){
    GNPacket msg;
    msg.UUID=this->UDID;
    msg.data=jsonString;
    if(gns->sendNetPack(msg)>0){
        return true;
    }
    return false;
}
//获取信息
std::string NetAppCCJSController::get_message(){
    return "";
}