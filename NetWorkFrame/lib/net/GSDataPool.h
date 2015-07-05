//
//  GSDataPool.h
//  Created by othink on 14-8-22.
//

#include "PackDefine.h"
#include "GSDataPoolDelegate.h"
#include <map>

typedef void(*tfun)(std::string,int);

class GSDataPool{
private:
    pthread_mutex_t mutex;
    std::map<std::string,void*> dataMap;
public:
    GSDataPool(void){
        pthread_mutex_init(&mutex, NULL);
    }
    ~GSDataPool(void){
        pthread_mutex_destroy(&mutex);
    }
    void postData(std::string name,void* data){
        dataMap.insert(std::make_pair(name, data));
    }
    void* getData(std::string name){
        return dataMap[name];
    }
    void test(tfun a){
        a("ttttts",1234);
    }
};