#include "RedisSession.hpp"

int RedisSession::call(HTTPRequest *req, HTTPResponse *res)
{
    req->setSession(nullptr);
    return 0;
}