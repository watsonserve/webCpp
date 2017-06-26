//
//  Rotes.hpp
//  GHTTPd
//
//  Created by 王兴卓 on 16/6/11.
//  Copyright © 2016年 watsserve. All rights reserved.
//

#ifndef Rotes_hpp
#define Rotes_hpp

#include "Route.hpp"

#include "G/net/http/MiddleWare.hpp"

using namespace G;

class Route : public MiddleWare
{
public:
    virtual int call(HTTPRequest *req, HTTPResponse *res);
    
};

#endif /* Rotes_hpp */
