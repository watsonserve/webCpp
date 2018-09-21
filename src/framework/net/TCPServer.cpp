#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <thread>
#if defined(__APPLE__) || defined (__MACOSX__) || defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__) || defined(__bsdi__)
    #include <sys/event.h>
#endif
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

int TCPServer::setPort(int port)
{
    this->port = port;
    return port;
}

SOCKET TCPServer::initSocket()
{
    // 创建socket
    return TCPsetup(this->port);
}
