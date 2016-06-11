#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "G/net/TCPServer.hpp"
#include "G/net/http/Request.hpp"
#include "G/net/http/Response.hpp"
#include "G/net/http/Dispatcher.hpp"
#include "G/net/http/MiddleWare.hpp"
#include "httpd/RedisSession.hpp"
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

int parser(HTTPRequest *req, HTTPResponse *res)
{
    res->set("Connection", "close");
    res->set("Content-Type", "text/plain; charset=UTF-8");

	return 0;
}

int logger(HTTPRequest *req, HTTPResponse *res)
{
    printf("log: %d %s\n", ((StreamIO*)(res->getSock()))->getFd(), req->get("path").c_str() );
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
    TCPServer srv;
    Route routes;
    const int max = 512;

    HTTPResponse::initDict();
    dispatcher.init(max);
    dispatcher.use(parser);
    dispatcher.use(logger);
    //dispatcher.use(&cookie);
    //dispatcher.use(&session);
    dispatcher.use(&routes);
    dispatcher.use(except);

    srv.initPool(20, 64, 1);
    srv.setPort(8800);
    srv.setCert("");
    srv.setKey("");
    int ret = srv.service(&dispatcher, max, false);
    //dispatcher.task(STDIN_FILENO);
    printf("%s\n", strerror(ret));
    return 0;
}
