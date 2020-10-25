#ifndef _HTTP_SERVER_HPP_
#define _HTTP_SERVER_HPP_

#include "G/ThreadPool.hpp"
#include "G/event/EventListener.hpp"
#include "G/net/TCPServer.hpp"
#include "G/net/Protocoler.hpp"

using namespace G;

class HttpServer: virtual public TCPServer, virtual public Protocoler
{
protected:
    virtual void onConnect(SOCKET fd) override;
public:
    HttpServer(unsigned int);
    virtual ~HttpServer();
};

#endif
