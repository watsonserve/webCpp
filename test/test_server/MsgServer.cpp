#include "MsgServer.hpp"

using namespace G;

MsgServer::MsgServer(EventListener* listener, unsigned short port) : StreamServer(listener)
{
    this->setPort(port);
    this->initSocket();
}

MsgServer::~MsgServer() {}

int MsgServer::service(int max)
{
    return this->_service(this, max);
}

void MsgServer::onError(IOStream *, int)
{

}

void MsgServer::onClose(IOStream *)
{

}

void MsgServer::onData(IOStream *stream)
{
    char buf[BUFSIZ];
    int len;

    len = stream->read(buf, BUFSIZ);
    if (len < 1)
    {
        printf("exception: len = %d\n\n", len);
        stream->close();
        return;
    }
    buf[len] = 0;
    printf("%s\n--------\nover\n", buf);
    strcpy(buf, "HTTP1.1 200 OK\r\nContent-Length: 53\r\n\r\n<!DOCTYPE html><html><body>Hello world!</body></html>\0");
    stream->write(buf, 93);
}

void MsgServer::onWritten(IOStream *)
{
    stream->close();
}
