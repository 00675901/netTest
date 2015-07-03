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
    void postData(std::string,void*);
    void* getData(std::string);
};

