#ifndef _HANDLER_POOL_H_
#define _HANDLER_POOL_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "G/net/stream_socket.h"

typedef struct handler_pool
{
    size_t handler_size;
    size_t limit;
    struct event_listener_t * event_listener;
    // 柔性数组
    unsigned char mem[];
} handler_pool_t;

handler_pool_t* handler_pool(size_t, struct event_listener_t *);

void* handler_pool_handle(handler_pool_t *, SOCKET, struct sock_addr *, event_callback);

void* get_stream_socket(handler_pool_t *, SOCKET);

#endif
