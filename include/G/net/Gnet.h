#ifndef _GNET_H_
#define _GNET_H_

#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/un.h>

typedef int SOCKET;

typedef struct sock_addr
{
    struct sockaddr_in addr;
    socklen_t len;
} sock_addr_t;

typedef void (*connect_callback)(void *, SOCKET, sock_addr_t *);

#define closesocket(fd) close(fd)

SOCKET UDPsetup(const unsigned short);

SOCKET TCPsetCli(char *, unsigned short);

int tcp_service(const unsigned short, int, connect_callback, void*);

int unix_service(const char *, int, connect_callback, void*);

short clean(SOCKET);

void killwaitcd(SOCKET, char *, unsigned long);

unsigned short getIP4addr(char *, struct sockaddr);

#endif
