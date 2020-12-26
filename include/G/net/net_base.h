#ifndef _NET_BASE_H_
#define _NET_BASE_H_

#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/un.h>

typedef int SOCKET;

typedef struct sock_addr
{
    struct sockaddr_in addr;
    socklen_t len;
} sock_addr_t;

/**
 * @param context
 * @param client_socket
 * @param sock_addr
 */
typedef void (*connect_callback)(void *, SOCKET, struct sock_addr *);

#define closesocket(fd) close(fd)

SOCKET udp_setup(const unsigned short);

SOCKET tcp_client(char *, unsigned short);

int acceptor(SOCKET, int, connect_callback, void*);

int tcp_service(const unsigned short, int, connect_callback, void*);

int unix_service(const char *, int, connect_callback, void*);

short clean(SOCKET);

void killwaitcd(SOCKET, char *, unsigned long);

unsigned short get_ip4_addr(char *, struct sockaddr);

#endif
