#ifndef _HTTP_SRV_H_
#define _HTTP_SRV_H_

#include "G/net/stream_socket.h"

struct http_req_t {};

void recv_event(struct event_t);

struct stream_socket_t* new_http_req(SOCKET, struct sock_addr *);

void handle_http_req(void*, SOCKET, struct sock_addr *);

#endif
