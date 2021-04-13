#include "G/net/stream_socket.h"

// construct
struct stream_socket_t * new_stream_socket(struct stream_socket_t *sock, SOCKET fd, struct sock_addr *addr, event_callback on_data, void* ctx)
{
    struct stream_socket_t *sock;

    if (!memcpy(&(sock->addr), addr, sizeof(sock_addr_t)))
    {
        return NULL;
    }
    sock->ident = fd;
    sock->context = ctx;
    sock->function = on_data;
    return sock;
}

// private
void stream_socket_handle(struct stream_socket_t *self, struct event_listener_t *listener, event_type_t event_type)
{
    self->event_type = event_type;
    emit_event(listener, OPT_ADD, self);
}

void stream_socket_listen(struct stream_socket_t *self, struct event_listener_t *listener)
{
    stream_socket_handle(self, listener, EV_IN);
}

const ssize_t stream_socket_read(struct stream_socket_t *self, char *buf, const size_t len, struct event_listener_t *listener)
{
    const size_t recv_len = recv(self->ident, buf, len, 0);
    if (-1 != recv_len)
        stream_socket_handle(self, listener, EV_IN);
    return recv_len;
}

const ssize_t stream_socket_send(struct stream_socket_t *self, const char *buf, const int len, struct event_listener_t *listener)
{
    const ssize_t sent_len = send(self->ident, buf, len, 0);
    stream_socket_handle(self, listener, EV_OUT);
    return sent_len;
}

void stream_socket_shutdown(struct stream_socket_t *self, int how)
{
    shutdown(self->ident, how);
}

void stream_socket_close(struct stream_socket_t *self)
{
    SOCKET fd = self->ident;
    memset(self, 0, sizeof(struct stream_socket_t));
    clean(fd);
}
