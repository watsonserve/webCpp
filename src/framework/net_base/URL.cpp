//
//  URL.cpp
//  GHTTPd
//
//  Created by James on 16/8/31.
//  Copyright © 2016 watsserve. All rights reserved.
//

#include <vector>
#include "G/GUtil.hpp"
#include "G/net/URL.hpp"

using namespace G;

URL::URL()
{
    
}

int URL::parse(URL *ret, const std::string &uri)
{
    // (\w+)://(\w+?):(S+?)@([\w\.]+):*(\d*)/(.+)\?*(.*)#*(.*)
    // scheme :// username : password @ domain : port / path ? query # hash
    size_t i;
    size_t off;
    std::string arg;
    std::vector<std::string> kvs;

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
        ret->path = arg.substr(off);
        arg.erase(off);
        
        off = ret->path.find('#');
        if (std::string::npos != off) // 有hash
        {
            ret->hash = ret->path.substr(off);
            ret->path.erase(off);
        }
        off = ret->path.find('?');
        if (std::string::npos != off) // 有参数
        {
            ret->search = ret->path.substr(off + 1);
            ret->path.erase(off);
        }
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
    // 解析get参数
    split(kvs, ret->search, "&");
    for (i = 0; i < kvs.size(); i++)
    {
        string &item = kvs[i];
        off = item.find('=');
        if (std::string::npos != off)
        {
            ret->query[item.substr(0, off)] = item.substr(off + 1);
        }
    }
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

const std::map<std::string, std::string> & URL::queryMap()
{
    return this->query;
}

std::string URL::getQuery(const std::string &key)
{
    return this->query[key];
}

std::string URL::getHash()
{
    return this->hash;
}
