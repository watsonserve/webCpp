#include "G/net/UNIXSocket.hpp"

using namespace G;

UNIXSocket::UNIXSocket(const char *path)
{
    this->sockfd = -1;
    this->setPath(path);
}

UNIXSocket::UNIXSocket(std::string &path)
{
    this->sockfd = -1;
    this->setPath(path);
}

G::UNIXSocket::~UNIXSocket()
{
    if (-1 == this->sockfd) return;
    close(this->sockfd);
}

int UNIXSocket::setPath(const char *str)
{
    this->path = str;
    return 0;
}

int UNIXSocket::setPath(std::string &str)
{
    this->path = str;
    return 0;
}

void UNIXSocket::initSocket()
{
    // 创建socket
    this->sockfd = UNIXsetup(this->path.c_str());
}
