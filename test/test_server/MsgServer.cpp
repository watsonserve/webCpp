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
        printf("msgServer onData: %d exception: %s\n", errno, strerror(errno));
        stream->close();
    }
    if (len < 1)
    {
        printf("msgServer onData len < 1\n");
        return;
    }
    buf[len] = 0;
    printf("%s-------- over\n", buf);
    strcpy(buf, "HTTP/1.1 404 NOT FOUND\r\nContent-Length: 54\r\n\r\n<!DOCTYPE html><html><body>404 Not Found</body></html>\0");
    stream->write(buf, 101);
}

void MsgServer::onWritten(IOStream *stream)
{
    printf("written\n");
    char buf[BUFSIZ];
    int len;

    len = stream->read(buf, BUFSIZ);
    if (len < 0)
    {
        printf("msgServer onWritten debug: %s\n", strerror(errno));
        stream->close();
        return;
    }
    if (len)
    {
        printf("msgServer onWritten found: %s\n", buf);
    }
    // stream->close();
}
