#ifndef _STREAM_SOCKET_HPP_
#define _STREAM_SOCKET_HPP_

#include "G/net/net_base.h"
#include "G/kit.h"

struct stream_socket_t
{
    SOCKET fd;
    struct sock_addr addr;
    event_callback onData;
};

void stream_socket_set_listener(event_listener_t *);
void stream_socket_listen(struct stream_socket_t *);
const ssize_t stream_socket_read(struct stream_socket_t *, char *, const size_t);
const ssize_t stream_socket_send(struct stream_socket_t *, const char *, const int);
void stream_socket_shutdown(struct stream_socket_t *, int);
void stream_socket_close(struct stream_socket_t *);

#endif
