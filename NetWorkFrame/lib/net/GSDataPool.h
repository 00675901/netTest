//
//  GSDataPool.h
//  Created by othink on 14-8-22.
//

#include <iostream>
#include <map>

class GSDataPool{
private:
    pthread_mutex_t mutex;
    GSDataPool(void);
    ~GSDataPool(void);
    std::map<std::string,void*> dataMap;
public:
    static GSDataPool* shareInstance();
//    void postData(std::string,void*);
//    void* getData(std::string);
    
    template<typename T> void postData(std::string name,void* data){
        std::cout<<"inneel key:"<<dataMap.size()<<std::endl;
        printf("%p\n",data);
        std::map<std::string,int>* bcs=(std::map<std::string,int>*)data;
        std::cout<<"innnnn:"<<bcs->size()<<std::endl;
        
//        pthread_mutex_lock(&mutex);
        dataMap.insert(std::make_pair(name, data));
        printf("%p\n",dataMap[name]);
        
        std::map<std::string,int>* bcss=(std::map<std::string,int>*)dataMap[name];
        std::cout<<"111111:"<<bcss->size()<<std::endl;
        
//        pthread_mutex_unlock(&mutex);
    }
    
    std::map<std::string,int>* getData(std::string name){
        std::cout<<"inneel key("<<name<<"):"<<dataMap.size()<<std::endl;
        
        std::map<std::string,int>* tempdata;
//        pthread_mutex_lock(&mutex);
        tempdata=static_cast<std::map<std::string,int>*>(dataMap[name]);
        printf("%p\n",tempdata);
        
//        std::map<std::string,int>* bcs=(std::map<std::string,int>*)tempdata;
        std::cout<<"222222:"<<tempdata->size()<<std::endl;
//        pthread_mutex_unlock(&mutex);
        return tempdata;
    }
};