#include "G/net/UNIXServer.hpp"

using namespace G;

UNIXServer::UNIXServer()
{
	this->isA = "UNIXServer";
}

UNIXServer::UNIXServer(const char *path)
{
	this->setPath(path);
}

UNIXServer::UNIXServer(std::string &path)
{
	this->setPath(path);
}

UNIXServer::~UNIXServer() {}

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
