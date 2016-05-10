#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <aio.h>
#include "G/net/TCPServer.hpp"
#include "G/net/http/Request.hpp"
#include "G/net/http/Response.hpp"
#include "G/net/http/Dispatcher.hpp"
#include "G/net/http/MiddleWare.hpp"
#include "httpd/RedisSession.hpp"

class GCookie : public MiddleWare
{
public:
    GCookie() {};
    virtual ~GCookie() {};
    int call(HTTPRequest *req, HTTPResponse *res);
};

int GCookie::call(HTTPRequest *req, HTTPResponse *res)
{
    res->set("Cookie", "domin=watsonserve.com");
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

int routes(HTTPRequest *req, HTTPResponse *res)
{
    if(req->get("path") == "/")
    {
        res->setContent("hello world\r\n");
        res->end();
        return 1;
    }
    return 0;
}

int except(HTTPRequest *req, HTTPResponse *res)
{
    res->setCode(500);
    res->setContent("a exception");
    res->send();
    return 1;
}

int main(int argc, char *argv[])
{
    HTTPDispatcher dispatcher;
    GCookie cookie;
    RedisSession session;
    TCPServer srv;
    const int max = 512;
#if defined (__linux__) || defined(__linux)
    struct aioinit aioInit;
    
    aioInit.aio_threads = 20;   // Maximum number of threads
    aioInit.aio_num = 64;       // Number of expected simultaneous requests
    aioInit.aio_idle_time = 1;  // Number of seconds before idle thread terminates (since glibc 2.2)
    aio_init(&aioInit);
    puts("on linux use aio 20 threads and simultaneous 64 idle 1");
#endif
    HTTPResponse::initDict();
    dispatcher.init(max);
    dispatcher.use(parser);
    dispatcher.use(logger);
    //dispatcher.use(&cookie);
    //dispatcher.use(&session);
    dispatcher.use(routes);
    dispatcher.use(except);

    srv.setPort(8800);
    srv.setCert("");
    srv.setKey("");
    int ret = srv.service(&dispatcher, max, false);
    //dispatcher.task(STDIN_FILENO);
    printf("%s\n", strerror(ret));
    return 0;
}
