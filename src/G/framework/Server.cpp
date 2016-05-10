//
//  Server.cpp
//  GHTTPd
//
//  Created by 王兴卓 on 16/4/12.
//  Copyright © 2016年 watsserve. All rights reserved.
//

#include "G/net/Server.hpp"

using namespace G;

int Server::setPort(int port)
{
    this->port = port;
    return port;
}