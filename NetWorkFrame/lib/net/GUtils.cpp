//
//  Utils.cpp
//  TestCocos2dx
//

#include "GUtils.h"

int GUtils::bytes2int(const char* bytes){
    return atoi(bytes);
}

std::string GUtils::itos(int i){
    std::stringstream s;
    s<<i;
    return s.str();
}

std::string GUtils::cptos(char* s){
    std::string ss(s);
    return ss;
}

int GUtils::ctoi(const char* c){
    int r;
    std::stringstream ss;
    ss<<c;
    ss>>r;
    return r;
}
