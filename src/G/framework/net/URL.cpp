//
//  URL.cpp
//  GHTTPd
//
//  Created by 王兴卓 on 16/8/31.
//  Copyright © 2016年 watsserve. All rights reserved.
//

#include <regex.h>
#include "G/net/URL.hpp"

using namespace G;

URL::URL()
{
    
}

int URL::parse(URL *ret, const std::string &uri)
{
    // (\w+)://(\w+?):(S+?)@([\w\.]+):*(\d*)/(.+)\?*(.*)#*(.*)
    // scheme :// username : password @ domain : port / path ? query # hash
    size_t off;
    std::string arg, tmp;

    arg = uri;
    off = arg.find("://");
    if (std::string::npos != off)
    {
        ret->scheme = arg.substr(0, off);
        arg.erase(0, off + 3);
    }
    else if (arg[0] == arg[1] && '/' == arg[0])
    {
        arg.erase(0, 2);
    }
    off = arg.find('/');
    if (std::string::npos != off) // 有路径
    {
        tmp = arg.substr(off);
        arg.erase(off);
    }
    off = arg.find('@');
    if (std::string::npos != off) // 有用户
    {
        ret->user = arg.substr(0, off);
        arg.erase(0, off + 1);
        off = ret->user.find(':');
        if (std::string::npos != off) // 有密码
        {
            ret->password = ret->user.substr(off + 1);
            ret->user.erase(off);
        }
    }
    off = arg.find(':');
    if (std::string::npos != off) // 有端口
    {
        sscanf(arg.substr(off + 1).c_str(), "%u", &(ret->port));
        arg.erase(off);
    }
    ret->domain = arg;
    printf("%s :// %s : %s @ %s : %u\n", ret->scheme.c_str(), ret->user.c_str(), ret->password.c_str(), ret->domain.c_str(), ret->port);
    return 0;
}

URL::~URL()
{
    
}

std::string URL::getScheme()
{
    return this->scheme;
}

std::string URL::getDomain()
{
    return this->domain;
}

int URL::getPort()
{
    return this->port;
}

std::string URL::getPath()
{
    return this->path;
}

std::string URL::getSearch()
{
    return this->search;
}

std::string URL::getQuery(const std::string &key)
{
    return this->query[key];
}

std::string URL::getHash()
{
    return this->hash;
}
