//
//  StreamServer.cpp
//  GHTTPd
//
//  Created by 王兴卓 on 16/4/12.
//  Copyright © 2016年 watsserve. All rights reserved.
//
#include "G/net/StreamServer.hpp"

G::StreamServer::StreamServer()
{
    this->isA = "StreamServer";
}

void G::StreamServer::initStreamServer(G::EventListener *listener)
{
    this->listener = listener;
}

// 静态
void G::StreamServer::onData(G::Event &ev)
{
    G::Protocoler *protocoler = (G::Protocoler *)(ev.context);
    const int fd = ev.ident;
    G::event_type_t event_type = ev.event_type;
    // @TODO
    return protocoler->onData(fd, event_type);
}

int G::StreamServer::_service(G::Protocoler *protocoler, int max)
{
    int errorNo;
    SOCKET sockfd, clientFd;
    struct sockaddr addr;
    socklen_t len;
    G::Event event;

    max &= 0x7FFFFFFF;
    sockfd = this->initSocket();
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
            fprintf(stderr, "Too many connect, denial of service");
            continue;
        }

        // 正常情况
        event.ident = clientFd;
        event.event_type = EV_IN;
        event.context = protocoler;
        event.function = G::StreamServer::onData;
        // onData
        listener->emit(OPT_ADD, event);
    }
    return 0;
}
