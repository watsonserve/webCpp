#include "MsgServer.hpp"

using namespace G;

void MsgServer::onData(IOStream &stream)
{
    char buf[BUFSIZ];
    int len;

    printf("event: %lX, fd: %d\n\n", event_type, fd);
    len = recv(fd, buf, BUFSIZ, 0);
    if (len < 1)
    {
        printf("exception: len = %d\n\n", len);
        close(fd);
        return;
    }
    buf[len] = 0;
    printf("%s\n--------\nover\n", buf);
    strcpy(buf, "HTTP1.1 200 OK\r\nContent-Length: 53\r\n\r\n<!DOCTYPE html><html><body>Hello world!</body></html>\0");
    send(fd, buf, 93, 0);
    close(fd);
}

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
