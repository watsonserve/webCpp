//
//  StreamServer.cpp
//  GHTTPd
//
//  Created by 王兴卓 on 16/4/12.
//  Copyright © 2016年 watsserve. All rights reserved.
//
#include "G/net/StreamServer.hpp"

G::StreamServer::StreamServer(G::EventListener *listener) : StreamServer(-1, listener) {}

G::StreamServer::StreamServer(SOCKET sockfd, G::EventListener *listener)
{
    this->sockfd = sockfd;
    this->listener = listener;
}

G::StreamServer::~StreamServer() {
    G::IOStream::clean();
}

int G::StreamServer::_service(G::IOHandler *ioHandler, int max)
{
    int errorNo;
    SOCKET clientFd;
    struct sockaddr addr;
    socklen_t len;

    max &= 0x7FFFFFFF;
    if (-1 == sockfd) {
        perror("Can't create socket");
        return -1;
    }

    // 监听循环
    while (1)
    {
        clientFd = accept(sockfd, &addr, &len);
        if (-1 == clientFd) {
            // 系统层错误
            errorNo = errno;
            perror("accept");
            // TODO
            if (EBADF == errorNo || EINVAL == errorNo)
                return -1;
            continue;
        }

        // 用户层错误
        if (max <= clientFd)
        {
            close(clientFd);
            fprintf(stderr, "Too many connect, denial of service\n");
            continue;
        }

        G::IOStream::newInstance(listener, clientFd, FD_SOCKET, ioHandler);
    }
    return 0;
}
