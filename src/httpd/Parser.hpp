//
//  Parser.hpp
//  GHTTPd
//
//  Created by 王兴卓 on 16/6/22.
//  Copyright © 2016年 watsserve. All rights reserved.
//

#ifndef _Parser_hpp_
#define _Parser_hpp_

#include "G/net/http/MiddleWare.hpp"

namespace G
{

    class Parser : public MiddleWare
    {
        virtual int initReq(HTTPRequest *req, StreamIO *fh);
    public:
        virtual int call(HTTPRequest *req, HTTPResponse *res);
    };

}

#endif /* Parser_hpp */
