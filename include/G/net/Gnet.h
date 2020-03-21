#ifndef _GNET_H_
#define _GNET_H_

#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/un.h>

typedef int SOCKET;

#define closesocket(fd) close(fd)

SOCKET UDPsetup(const unsigned short);

SOCKET TCPsetup(const unsigned short);

SOCKET UNIXsetup(const char *);

SOCKET TCPsetCli(char *, unsigned short);

short clean(SOCKET);

void killwaitcd(SOCKET, char *, unsigned long);

unsigned short getIP4addr(char *, struct sockaddr);

#endif
