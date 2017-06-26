#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <thread>
#if defined(__APPLE__) || defined (__MACOSX__) || defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__) || defined(__bsdi__)
    #include <sys/event.h>
#endif
#include "G/IOHandle.hpp"
#include "G/net/UNIXServer.hpp"

using namespace G;

UNIXServer::UNIXServer()
{
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
