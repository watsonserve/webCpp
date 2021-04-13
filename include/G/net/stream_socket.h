#ifndef _STREAM_SOCKET_H_
#define _STREAM_SOCKET_H_

#include <stdio.h>
#include <string.h>
#include "G/net/net_base.h"
#include "G/kit.h"

struct stream_socket_t
{
    _EVENT_FIELDS_
    struct sock_addr addr;
};

// construct
struct stream_socket_t * new_stream_socket(struct stream_socket_t *, SOCKET, struct sock_addr *, event_callback, void*);

void stream_socket_listen(struct stream_socket_t *, struct event_listener_t *);

const ssize_t stream_socket_read(struct stream_socket_t *, char *, const size_t, struct event_listener_t *);

const ssize_t stream_socket_send(struct stream_socket_t *, const char *, const int, struct event_listener_t *);

void stream_socket_shutdown(struct stream_socket_t *, int);

void stream_socket_close(struct stream_socket_t *);
#endif
