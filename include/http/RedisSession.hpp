#ifndef _REDISSESSION_HPP_
#define _REDISSESSION_HPP_

#include "G/net/http/MiddleWare.hpp"

using namespace G;

class RedisSession : public MiddleWare
{
    public:
        virtual int call(HTTPRequest *req, HTTPResponse *res);
};

#endif