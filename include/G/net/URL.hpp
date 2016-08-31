//
//  URL.hpp
//  GHTTPd
//
//  Created by 王兴卓 on 16/8/31.
//  Copyright © 2016年 watsserve. All rights reserved.
//

#ifndef URL_h
#define URL_h

#include <string>
#include <map>
#include "G/Object.hpp"

namespace G {

    class URL : public Object {
        std::string scheme;
        std::string domain;
        int port;
        std::string path;
        std::string search;
        std::string hash;
        std::map<std::string, std::string> query;
        URL();
        
    public:
        static URL parse(std::string &uri);
        virtual ~URL();
        std::string getScheme();
        std::string getQuery(const std::string &);
        std::string getSearch();
        std::string getHash();
        std::string getDomain();
        int getPort();
        std::string getPath();
    };
    
}

#endif /* URL_h */
