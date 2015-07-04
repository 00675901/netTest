//
//  GSDataPool.cpp
//  Created by othink on 14-8-22.
//

#include "GSDataPool.h"

static GSDataPool *gsnInstance;

GSDataPool::GSDataPool(void){
    pthread_mutex_init(&mutex, NULL);
}
GSDataPool::~GSDataPool(void){
    pthread_mutex_destroy(&mutex);
}

GSDataPool* GSDataPool::shareInstance(){
    if (!gsnInstance) {
        gsnInstance=new GSDataPool();
    }
    return gsnInstance;
}