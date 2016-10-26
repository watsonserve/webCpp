#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <thread>
#if defined(__APPLE__) || defined (__MACOSX__) || defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__) || defined(__bsdi__)
    #include <sys/event.h>
#endif
extern "C" {
    #include "G/net/Gnet.h"
}
#include "G/IOHandle.hpp"
#include "G/net/TCPServer.hpp"

/*
#include "openssl/rsa.h"
#include "openssl/crypto.h"
#include "openssl/x509.h"
#include "openssl/pem.h"
#include "openssl/ssl.h"
#include "openssl/err.h"
*/

using namespace G;

TCPServer::TCPServer() {}

TCPServer:: ~TCPServer() {}


int TCPServer::setCert(const char *certFile)
{
    if (NULL == certFile)
    {
        return -1;
    }
    return 0;
}

int TCPServer::setKey(const char *keyFile)
{
    if (NULL == keyFile)
    {
        return -1;
    }
    return 0;
}

int TCPServer::initPool(int thr, int simu, int idleTime)
{
    struct aioinit aioInit;
    
    aioInit.aio_threads = thr;   // Maximum number of threads
    aioInit.aio_num = simu;       // Number of expected simultaneous requests
    aioInit.aio_idle_time = idleTime;  // Number of seconds before idle thread terminates (since glibc 2.2)
    Aio::aioInit(&aioInit);

    return 0;
}

#if defined(__APPLE__) || defined (__MACOSX__) || defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__) || defined(__bsdi__) || defined (__linux__) || defined(__linux)
int TCPServer::service(IOEvents *dispatcher, int max)
{
    int i, errorNo;
    SOCKET sockfd, clientFd;
    struct sockaddr addr;
    socklen_t len;
    StreamIO *ioHandles;
    char *mem;

    // 创建socket
    sockfd = TCPsetup(port);
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
    for(i=0; i<max; i++)
    {
        if( NULL == StreamIO::init(ioHandles + i, dispatcher, mem + (i*BUFSIZ), BUFSIZ))
            exit(1);
    }

    // 网络监听循环
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
int TCPServer::service(IOEvents *dispatcher, int max)
{
    int pfd, i;
    SOCKET sockfd, clientFd;
    struct sockaddr addr;
    socklen_t len;
    StreamIO *ioHandles;
    char *mem;
    struct pollfd *fds;
    nfds_t nfds;
    
    sockfd = TCPsetup(port);    // 创建socket
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

int TCPServer::serviceSafe(IOEvents *dispatcher, int max)
{
//     int howMuch, i, epfd;
//     SOCKET sockfd, clientFd;
//     struct sockaddr addr;
//     socklen_t len;
//     struct epoll_event *events;
//     ClientInfo *clientInfos;
//     GException err;

//     SSL_METHOD *meth;
//     SSL_load_error_strings();
//     SSLeay_add_ssl_algorithms();
//     meth = SSLv3_server_method();
// /* set SSL */
//     ctx = SSL_CTX_new (meth);
//     if(!ctx) {
//         err.setMsg("");
//         throw err;
//     }
//     if((!SSL_CTX_load_verify_locations(ctx, CAFILE, NULL)) || (!SSL_CTX_set_default_verify_paths(ctx))) {
//         err.setMsg("");
//         throw err;
//     }
//     if (SSL_CTX_use_certificate_file(ctx, CERTF, SSL_FILETYPE_PEM) <= 0) {
//         err.setMsg("");
//         throw err;
//     }
//     if (SSL_CTX_use_PrivateKey_file_pass(ctx, KEYF, "123456") <= 0) {
//         err.setMsg("");
//         throw err;
//     }
//     if (!SSL_CTX_check_private_key(ctx)) {
//         fprintf(stderr,"Private key does not match the certificate public key\n");
//         exit(5);
//     }
//     s_server_verify = SSL_VERIFY_PEER | SSL_VERIFY_FAIL_IF_NO_PEER_CERT | SSL_VERIFY_CLIENT_ONCE;
//     SSL_CTX_set_verify( ctx, s_server_verify, verify_callback_server );
//     SSL_CTX_set_client_CA_list( ctx, SSL_load_client_CA_file(CAFILE) );
// /* set TCP */
//     sockfd = TCPsetup(port);
//     if( -1 == sockfd ) {
//         return -1;
//     }
//     clientInfos = (ClientInfo *)malloc( max * sizeof(ClientInfo));
//     if( NULL == clientInfos)
//         return -1;
//     events = (struct epoll_event *)malloc( max * sizeof(struct epoll_event) );
//     if( NULL == events ) {
//         free(clientInfos);
//         return -1;
//     }
//     for(i=0; i<max; i++)
//     {
//         events[i].data.ptr = clientInfos + i;
//     }
//     epfd = epoll_create( max );
//     if( -1 == epfd ) {
//         free(events);
//         return -1;
//     }
//     while(1)
//     {
//         howMuch = epoll_pwait(epfd, events, max, 0, NULL);
//         if( -1 == howMuch ) {
//             return -1;
//         }
//         for(i=0; i<howMuch; i++)
//         {
//             clientFd = ((ClientInfo *)(events[i].data.ptr))->fd;
//             if( clientFd == sockfd )  // a new client
//             {
//                 clientFd = accept(sockfd, &addr, &len);
//                 if( -1 == clientFd )
//                 {
//                     return -1;
//                 }
//                 ssl = SSL_new(ctx);
//                 CHK_NULL(ssl);
//                 err = SSL_set_fd(ssl, clientFd);
//                 epoll_ctl(epfd, EPOLL_CTL_ADD, clientFd, events + i);
//                 continue;
//             }
//             // a message
//             Aio::aioRead(clientFd);
//             epoll_ctl(epfd, EPOLL_CTL_ADD, clientFd, events + i);
//             continue;
//         }
//     }
//     SSL_CTX_free(ctx);
     return 0;
}

int TCPServer::service(IOEvents *dispatcher, int max, int sslFlag)
{
    if(sslFlag)
        return this->serviceSafe(dispatcher, max);
    return this->service(dispatcher, max);
}
