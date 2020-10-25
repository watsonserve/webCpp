//
//  Parser.hpp
//  GHTTPd
//
//  Created by 王兴卓 on 16/6/22.
//  Copyright © 2016年 watsserve. All rights reserved.
//

#ifndef _PARSER_HPP_
#define _PARSER_HPP_

#include "http/request.hpp"
#include "http/response.hpp"

namespace G_HTTP {

    class Parser
    {
    public:
        Parser();
        virtual ~Parser();
        void scan(const char *buf, const int len);
        
    };

}

#endif /* Parser_hpp */
