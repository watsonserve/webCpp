//
//  URL.cpp
//  GHTTPd
//
//  Created by 王兴卓 on 16/8/31.
//  Copyright © 2016年 watsserve. All rights reserved.
//

#include "G/net/URL.hpp"

using namespace G;

URL::URL()
{
    
}

URL URL::parse(const std::string &arg)
{
    // (\w+)://([\w\.]+):*(\d*)/(.+)\?*(.*)#*(.*)
    URL ret;
    std::string uri;
    unsigned int i;

    uri = arg;
    for (i=0; i<uri.length(); i++)
    {
        switch(uri[i])
        {
            case ':':
                if(0 == ret.scheme.length())
                {
                    ret.scheme = uri.substr(0, i);
                    uri.erase(0, i);
                }
                break;
            case '?':
                tmpFlag = 1;
                tmp = tmp.erase(0, i+1);
                break;
            else
            {
                tmpFlag = 2;
            }
            break;
        }
    }
    if (0 == tmpFlag)
    {
        request->set("path", tmp);
    }
    if (1 == tmpFlag)  /* set query */
    {
        int begin = 0;
        int kvFlag = 0;
        string key;
        unsigned int i;
        for (i=0; i<tmp.length(); i++)
        {
            switch (tmp[i])
            {
                case '=':
                    key = tmp.substr(begin, i-begin);
                    kvFlag = 1;
                    break;
                case '&':
                    if(kvFlag)
                    {
                        request->_GET.set(key, tmp.substr(begin, i-begin));
                        kvFlag = 0;
                    }
                    break;
                default:
                    continue;
            }
            begin = i +1;
        }
        if (kvFlag)
        {
            if (0 == i-begin)
                request->_GET.set(key, "");
            else
                request->_GET.set(key, tmp.substr(begin, i-begin));
        }
    }
    return ret;
}

URL::~URL()
{
    
}

std::string URL::getScheme()
{
    
}

std::string URL::getDomain()
{
    
}

int URL::getPort()
{
    
}

std::string URL::getPath()
{
    
}

std::string URL::getSearch()
{
    
}

std::string URL::getQuery(const std::string &key)
{
    
}

std::string URL::getHash()
{
    
}
