//
//  Route.cpp
//  GHTTPd
//
//  Created by 王兴卓 on 16/6/11.
//  Copyright © 2016年 watsserve. All rights reserved.
//
extern "C" {
#include <stdio.h>
}
#include "Route.hpp"

int Route::call(HTTPRequest *req, HTTPResponse *res)
{
    std::string path = req->get("path");
    if("/" == path || "/index.json" == path)
    {
        puts(path.c_str());
        res->setContent("{\"hello\": \"world\"}\r\n");
        res->end();
        return 1;
    }
    printf("fine");
    return 0;
}