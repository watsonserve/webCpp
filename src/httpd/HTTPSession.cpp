#include "RedisSession.hpp"

int RedisSession::call(HTTPRequest *req, HTTPResponse *res)
{
    req->setSession(NULL);
    return 0;
}