#include "MsgServer.hpp"

using namespace G;

MsgServer::MsgServer(EventListener* listener, unsigned short port) : StreamServer(listener)
{
    this->sockfd = TCPsetup(port);
}

MsgServer::~MsgServer() {}

int MsgServer::service(int max)
{
    return this->_service(this, max);
}

void MsgServer::onOpen(IOStream *stream)
{
    printf("onOpen\n");
}

void MsgServer::onError(IOStream *s, int e)
{
    printf("onError: %s\n", strerror(e));
}

void MsgServer::onClose(IOStream *stream)
{
    printf("onClose\n");
}

void MsgServer::onData(IOStream *stream)
{
    char buf[BUFSIZ];
    int len;

    len = stream->read(buf, BUFSIZ);
    if (len < 0)
    {
        printf("msgServer onData exception: %s\n", strerror(errno));
        stream->close();
    }
    if (len < 1)
    {
        return;
    }
    buf[len] = 0;
    printf("%s-------- over\n", buf);
    strcpy(buf, "HTTP/1.1 200 OK\r\nContent-Length: 53\r\n\r\n<!DOCTYPE html><html><body>Hello world!</body></html>\0");
    stream->write(buf, 94);
}

void MsgServer::onWritten(IOStream *stream)
{
    printf("close!!\n");
    stream->close();
}
