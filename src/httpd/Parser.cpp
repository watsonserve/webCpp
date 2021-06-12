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

/* 开始解析post参数 */
int Parser::initReq(HTTPRequest *req, StreamIO *fh)
{
    contentType = req->get("Content-Type");
    if( "multipart/form-data" == contentType.substr(0, 19) )    /* multipart/form-data; boundary=----XXXX */
    {
        boundary = contentType.substr(30);
        /* to do */
    }
    else
    {
        vector<string> bar;
        split(foo, gram[1], "&");    /* 分割get参数 */
        len = foo.size();
        for(int i=0; i<len; i++)    /* 设定从第二行开始的每一行 */
        {
            split(bar, foo[i], "=");    /* 分割键值对 */
            req->_POST.set(bar[0], bar[1]);
        }
    }
    return 0;
}

int Parser::call(HTTPRequest *req, HTTPResponse *res)
{
    initReq(req, (StreamIO*)req->getSock());
    initRes(res);
    return 0;
}