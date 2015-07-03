//
//  GUtils.h
//  TestCocos2dx
//

#ifndef __TestCocos2dx__GUtils__
#define __TestCocos2dx__GUtils__

#include <iostream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>

typedef int8_t int8;

class GUtils{
public:
    static int bytes2int(const char* bytes);
    static void int2bytes(int i,unsigned char* bytes);
    static std::string itos(int i);
    static std::string cptos(char* s);
    static int ctoi(const char* c);
};

#endif /* defined(__TestCocos2dx__GUtils__) */
