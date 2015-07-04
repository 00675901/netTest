//
//  GSDataPool.h
//  Created by othink on 14-8-22.
//

#include <iostream>
#include <map>

template<class T>
class GSTestDataPool{
private:
    pthread_mutex_t mutex;
    T* GSData;
public:
    GSTestDataPool(T* dp): GSData(dp){
        pthread_mutex_init(&mutex, NULL);
        printf("GSDataPool Create\n");
    }
    ~GSTestDataPool(void){
        pthread_mutex_destroy(&mutex);
        printf("GSDataPool Destroy\n");
    }
    T getData(){
        return GSData;
    }
};