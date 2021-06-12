#include "http/server.hpp"

using namespace G;

void HttpServer::onData(TCPSocket *sock, event_type_t event_type)
{
    int len;
    char buf[BUFSIZ];
    char header[] = "HTTP1.1 200 OK\r\nContent-Type: text/html;charset=utf-8\r\nContent-Length: 53\r\n\r\n";
    char body[] = "<!DOCTYPE html><html><body>Hello world!</body></html>";

    // printf("event: %lX, fd: %d\n\n", event_type, sock->fd);
    len = sock->read(buf, BUFSIZ);
    if (len < 1)
    {
        printf("exception: len = %d\n\n", len);
        close(fd);
        return;
    }
    buf[len] = 0;
    len = strlen(header);
    printf("%s\n--------\nover resp header len: %d\n", buf, len);

    // response
    strcpy(buf, header);
    strcpy(buf + len, body);
    send(fd, buf, len + strlen(body), 0);
    close(fd);
}

void HttpServer::onConnect(SOCKET fd) {
    StreamSocket::handle(new HttpProto());
}

HttpServer::HttpServer(unsigned int port)
{
    this->setPort(port);
}

HttpServer::~HttpServer()
{
}
