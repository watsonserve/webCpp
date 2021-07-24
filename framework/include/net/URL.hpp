//
//  URL.hpp
//  GHTTPd
//
//  Created by James on 16/8/31.
//  Copyright © 2016 watsserve. All rights reserved.
//

#ifndef _URL_H_
#define _URL_H_

#include <string>
#include <map>
#include "G/Object.hpp"

namespace G
{

    class URL : virtual public Object {
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

#endif /* _URL_H_ */
