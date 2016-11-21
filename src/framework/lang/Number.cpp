//
//  Number.cpp
//  GHTTPd
//
//  Created by 王兴卓 on 16/9/25.
//  Copyright © 2016年 watsserve. All rights reserved.
//

#include "G/Number.hpp"

using namespace G;

long Number::parseInt(const char * str)
{
    long ret;

    sscanf(str, "%ld", &ret);
    return ret;
}

unsigned long Number::parseUInt(const char * str)
{
    unsigned long ret;
    
    sscanf(str, "%lu", &ret);
    return ret;
}

long long Number::parseInt64(const char * str)
{
    long long ret;
    
    sscanf(str, "%lld", &ret);
    return ret;
}

unsigned long long Number::parseUInt64(const char * str)
{
    unsigned long long ret;
    
    sscanf(str, "%llu", &ret);
    return ret;
}

std::string Number::stringify(long long src)
{
    char buf[24];
    std::string ret;

    sprintf(buf, "%lld", src);
    ret = buf;
    return ret;
}

std::string Number::stringify(unsigned long long src)
{
    char buf[24];
    std::string ret;
    
    sprintf(buf, "%llu", src);
    ret = buf;
    return ret;
}
