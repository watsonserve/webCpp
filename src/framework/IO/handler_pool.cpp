#include "G/net/handler_pool.h"

handler_pool_t* handler_pool(size_t limit, size_t handler_size, struct event_listener_t * event_listener)
{
    size_t size = sizeof(size_t) + sizeof(struct event_listener_t *) + handler_size * limit;
    handler_pool_t *self = (handler_pool_t *)malloc(size);
    if (!self) return NULL;

    self->handler_size = handler_size;
    self->limit = limit;
    self->event_listener = event_listener;
    return self;
}

void* handler_pool_handle(handler_pool_t *self, SOCKET fd, struct sock_addr *addr, event_callback on_data)
{
    void *sock;

    if (self->limit <= fd)
        return NULL;
    sock = (self->mem) + self->handler_size * fd;
    if (!new_stream_socket((struct stream_socket_t *)sock, fd, addr, on_data, self))
        return NULL;
    return sock;
}

void* get_stream_socket(handler_pool_t *self, SOCKET fd)
{
    if (self->limit <= fd)
        return NULL;
    return (self->mem) + self->handler_size * fd;
}
