#ifndef _GNET_H_
#define _GNET_H_

#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/un.h>

typedef int SOCKET;

typedef struct sock_addr
{
    socklen_t len;
    struct sockaddr addr;
} sock_addr_t;

typedef void (*connect_callback)(void *, SOCKET, sock_addr_t *);

#define closesocket(fd) close(fd)

SOCKET UDPsetup(const unsigned short);

SOCKET UNIXsetup(const char *);

SOCKET TCPsetCli(char *, unsigned short);

int tcp_service(const unsigned short port, int limit, connect_callback on_conn, void* context);

short clean(SOCKET);

void killwaitcd(SOCKET, char *, unsigned long);

unsigned short getIP4addr(char *, struct sockaddr);

#endif
