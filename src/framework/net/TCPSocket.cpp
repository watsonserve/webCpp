#include "G/net/TCPSocket.hpp"

/*
#include "openssl/rsa.h"
#include "openssl/crypto.h"
#include "openssl/x509.h"
#include "openssl/pem.h"
#include "openssl/ssl.h"
#include "openssl/err.h"
*/

G::TCPSocket::TCPSocket()
{
    this->sockfd = -1;
}

G::TCPSocket::~TCPSocket()
{
    if (-1 == this->sockfd) return;
    close(this->sockfd);
}

int G::TCPSocket::setCert(const char *certFile)
{
    if (nullptr == certFile)
    {
        return -1;
    }
    return 0;
}

int G::TCPSocket::setKey(const char *keyFile)
{
    if (nullptr == keyFile)
    {
        return -1;
    }
    return 0;
}

int G::TCPSocket::setPort(unsigned short port)
{
    this->port = port;
    return port;
}

void G::TCPSocket::initSocket()
{
    // 创建socket
    this->sockfd = TCPsetup(this->port);
}
