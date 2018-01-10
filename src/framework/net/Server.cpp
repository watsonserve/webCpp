//
//  Server.cpp
//  GHTTPd
//
//  Created by 王兴卓 on 16/4/12.
//  Copyright © 2016年 watsserve. All rights reserved.
//
extern "C" {
#include <unistd.h>
#include <errno.h>
}
#include "G/net/Server.hpp"

using namespace G;

int Server::initPool(int thr, int simu, int idleTime)
{
    struct aioinit aioInit;
    
    aioInit.aio_threads = thr;   // Maximum number of threads
    aioInit.aio_num = simu;       // Number of expected simultaneous requests
    aioInit.aio_idle_time = idleTime;  // Number of seconds before idle thread terminates (since glibc 2.2)
    Aio::aioInit(&aioInit);

    return 0;
}

#if defined(__APPLE__) || defined (__MACOSX__) || defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__) || defined(__bsdi__) || defined (__linux__) || defined(__linux)
int Server::service(IOEvents *dispatcher, int max)
{
    int i, errorNo;
    SOCKET sockfd, clientFd;
    struct sockaddr addr;
    socklen_t len;
    StreamIO *ioHandles;
    char *mem;

    sockfd = this->initSocket();
    if( -1 == sockfd ) {
        perror("Can't create socket");
        return -1;
    }

    // 内存池
    mem = (char*)malloc(max * BUFSIZ);
    if(NULL == mem) {
        perror("alloc buffer");
        return -1;
    }

    // io句柄池
    ioHandles = new StreamIO[max];
    if(NULL == ioHandles) {
        perror("alloc IO handles");
        return -1;
    }

    // io句柄绑定缓存区
    for(i = 0; i < max; i++)
    {
        if( NULL == StreamIO::init(ioHandles + i, dispatcher, mem + (i * BUFSIZ), BUFSIZ))
            exit(1);
    }

    // 监听循环
    while(1)
    {
        clientFd = accept(sockfd, &addr, &len);
        if(-1 == clientFd) {
            // 系统层错误
            errorNo = errno;
            perror("accept");
            if (EBADF == errorNo || EINVAL == errorNo)
                return -1;
        }

        // 用户层错误
        if(clientFd >= max)
        {
            close(clientFd);
            fprintf(stderr, "Too many connect, denial of service");
            continue;
        }

        // 正常情况
        ioHandles[clientFd].setFd(clientFd, NET_SOCKET);
        ioHandles[clientFd].cleanCache();
        ioHandles[clientFd].listen();
    }
    return 0;
}
#else
int Server::service(IOEvents *dispatcher, int max)
{
    int pfd, i;
    SOCKET sockfd, clientFd;
    struct sockaddr addr;
    socklen_t len;
    StreamIO *ioHandles;
    char *mem;
    struct pollfd *fds;
    nfds_t nfds;
    
    sockfd = this->initSocket();
    if( -1 == sockfd ) {
        perror("Can't create socket");
        return -1;
    }

    fds = (struct pollfd *)malloc(max);
    if(NULL == fds)
    {
        perror("Can't create socket");
        return -1;
    }
    pfd = poll(fds, nfds, 0);
    return 0;
}
#endif
