#include "G/net/UNIXServer.hpp"

using namespace G;

UNIXServer::UNIXServer(G::EventListener *listener, const char *path)
{
    this->initStreamServer(listener);
    this->isA = "UNIXServer";
    this->setPath(path);
}

UNIXServer::UNIXServer(G::EventListener *listener, std::string &path)
{
    this->initStreamServer(listener);
    this->isA = "UNIXServer";
    this->setPath(path);
}

int UNIXServer::setPath(const char *str)
{
    this->path = str;
    return 0;
}

int UNIXServer::setPath(std::string &str)
{
    this->path = str;
    return 0;
}

SOCKET UNIXServer::initSocket()
{
    // 创建socket
    return UNIXsetup(this->path.c_str());
}
