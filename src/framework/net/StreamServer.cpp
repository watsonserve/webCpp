//
//  StreamServer.cpp
//  GHTTPd
//
//  Created by James on 16/4/12.
//  Copyright © 2016 watsserve. All rights reserved.
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

void G::StreamServer::onConnect(SOCKET fd, struct sockaddr addr, socklen_t len)
{
    G::IOHandler *ioHandler = handleGenerator(addr, len);
    G::IOStream::newInstance(listener, fd, FD_SOCKET, ioHandler);
}

int G::StreamServer::service(int max)
{
    return acceptor(sockfd, max, this->onConnect);
}
