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

G::StreamServer::~StreamServer()
{
    size_t i, siz;
    std::map<int, G::IOStream *>::iterator it = streams.begin();
    siz = streams.size();
    for(i = 0; i < siz; i++)
    {
        delete it->second;
        streams[it->first] = nullptr;
        it++;
    }
}

void G::StreamServer::listen(int fd, G::IOHandler *handler)
{
    G::IOStream *stream = streams[fd];
    if (nullptr == stream)
    {
        stream = new G::IOStream(listener, handler);
        streams[fd] = stream;
    }
    stream->setFd(fd, FD_SOCKET);
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

        this->listen(clientFd, ioHandler);
    }
    return 0;
}
