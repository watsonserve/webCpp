//
//  Parser.cpp
//  GHTTPd
//
//  Created by 王兴卓 on 16/6/22.
//  Copyright © 2016年 watsserve. All rights reserved.
//

#include <string>
#include <vector>
#include "Parser.hpp"
#include "G/GUtil.hpp"

using namespace std;
using namespace G;

int Parser::initReq(HTTPRequest *req, StreamIO *fh)
{
    int tmpFlag;
    string tmp, str, data, firstRow;
    vector<string> foo, bar;

    tmp = fh->gets();
    split(foo, tmp, " ");
    if(foo.size() != 3)
    {
        puts(tmp.c_str());
        exit(1);
    }
    req->set("method", foo[0]);
    req->set("protocol", foo[2]);
    tmp = foo[1];
    while (1)    /* 设定从第二行开始的每一行 */
    {
        str = fh->gets();
        if (str.empty())
            break;
        split(foo, str, ": ");    /* 获取第一行 'GET URI HTTP/1.1' */
        req->set(foo[0], foo[1]);
    }
    tmpFlag = 0;  /* 0 path, 1 args, 2 hash */
    for (unsigned int i=0; i<tmp.length(); i++)
    {
        if ('?' == tmp[i] || '#' == tmp[i])
        {
            str = tmp.substr(0, i);
            req->set("path", str);
            if ('?' == tmp[i])
            {
                tmpFlag = 1;
                tmp = tmp.erase(0, i+1);
            }
            else
            {
                tmpFlag = 2;
            }
            break;
        }
    }
    if (0 == tmpFlag)
    {
        req->set("path", tmp);
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
                        req->_GET.set(key, tmp.substr(begin, i-begin));
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
                req->_GET.set(key, "");
            else
                req->_GET.set(key, tmp.substr(begin, i-begin));
        }
    }
    return 0;
}
/* 开始解析post参数 */
    // contentType = request->get("Content-Type");
    // if( "multipart/form-data" == contentType.substr(0, 19) )    /* multipart/form-data; boundary=----XXXX */
    // {
    //     boundary = contentType.substr(30);
    //     /* to do */
    // }
    // else
    // {
    //     vector<string> bar;
    //     split(foo, gram[1], "&");    /* 分割get参数 */
    //     len = foo.size();
    //     for(int i=0; i<len; i++)    /* 设定从第二行开始的每一行 */
    //     {
    //         split(bar, foo[i], "=");    /* 分割键值对 */
    //         request->_POST.set(bar[0], bar[1]);
    //     }
    // }

int Parser::initRes(HTTPResponse *res)
{
    res->set("proto", "HTTP/1.1");
    res->set("code", "200");
    res->set("stat", "OK");
    res->set("Connection", "close");
    res->set("Content-Type", "text/plain; charset=UTF-8");
    return 0;
}

int Parser::call(HTTPRequest *req, HTTPResponse *res)
{
    initReq(req, req->getSock());
    initRes(res);
    return 0;
}