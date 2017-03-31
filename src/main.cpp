#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "G/webCpp.hpp"
#include "httpd/RedisSession.hpp"
#include "httpd/Parser.hpp"
#include "httpd/Route.hpp"

class GCookie : public MiddleWare
{
public:
    GCookie() {};
    virtual ~GCookie() {};
    int call(HTTPRequest *req, HTTPResponse *res);
};

int GCookie::call(HTTPRequest *req, HTTPResponse *res)
{
    res->set("Set-Cookie", "domin=watsonserve.com");
    return 0;
}

int logger(HTTPRequest *req, HTTPResponse *res)
{
    printf("log: %s\n", req->_GET.get("path").c_str());
    return 0;
}

int except(HTTPRequest *req, HTTPResponse *res)
{
    res->setCode(500);
    res->setContent("a exception");
    res->end();
    return 1;
}

int main(int argc, char *argv[])
{
    HTTPDispatcher dispatcher;
    GCookie cookie;
    RedisSession session;
    //Parser parser;
    TCPServer srv;
    Route routes;
    const int max = 512;

    HTTPResponse::initDict();
    dispatcher.init(max);
    //dispatcher.use(&parser);
    dispatcher.use(logger);
    dispatcher.use(&cookie);
    //dispatcher.use(&session);
    dispatcher.use(&routes);
    dispatcher.use(except);

    srv.initPool(20, 64, 1);
    srv.setPort(8800);
    srv.setCert("");
    srv.setKey("");
    int ret = srv.service(&dispatcher, max, false);
    printf("%s\n", strerror(ret));
    return 0;
}
