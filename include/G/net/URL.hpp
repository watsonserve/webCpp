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
        std::string user;
        std::string password;
        std::string domain;
        unsigned int port;
        std::string path;
        std::string search;
        std::string hash;
        std::map<std::string, std::string> query;
    public:
        static int parse(URL *, const std::string &uri);
        URL();
        virtual ~URL();
        std::string getScheme();
        std::string getQuery(const std::string &);
        const std::map<std::string, std::string> & queryMap();
        std::string getSearch();
        std::string getHash();
        std::string getDomain();
        int getPort();
        std::string getPath();
    };
    
}

#endif /* URL_h */
