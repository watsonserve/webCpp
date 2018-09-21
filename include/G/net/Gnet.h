#ifndef _GNET_H_
#define _GNET_H_

#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/un.h>

typedef int SOCKET;

#define closesocket(fd) close(fd)

SOCKET UDPsetup(const unsigned short port);

SOCKET TCPsetup(const unsigned short port);

SOCKET UNIXsetup(const char *path);

SOCKET TCPsetCli(char* HostAddr, unsigned short port);

short clean(SOCKET clinet_fd);

void killwaitcd(SOCKET cd, char *msg, unsigned long len);

unsigned short getIP4addr(char *readdr, struct sockaddr addr);

#endif
