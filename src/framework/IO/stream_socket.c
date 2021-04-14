#include "G/io/stream_socket.h"

// private
void _on_stream_data(struct event_t ev)
{
    struct stream_socket_t *sock;

    sock = (struct stream_socket_t *)(ev.self);
    const size_t recv_len = recv(ev.ident, sock->buf.zone, sock->buf.siz, 0);
    // @TODO
    // if (0 == recv_len)
    //     stream_socket_handle(self, listener, EV_IN);
    sock->buf.siz = recv_len;
    sock->parent_callback(sock, sock->buf);
}

// private
void stream_socket_handle(struct stream_socket_t *self, struct event_listener_t *listener, event_type_t event_type)
{
    self->event_type = event_type;
    emit_event(listener, OPT_ADD, self);
}

struct stream_socket_t * new_stream_socket(struct stream_socket_t *sock, SOCKET fd, struct sock_addr *addr, void* ctx)
{
    memset(sock, 0, sizeof(struct stream_socket_t));
    if (!memcpy(&(sock->addr), addr, sizeof(struct sock_addr)))
    {
        return NULL;
    }
    sock->ident = fd;
    sock->self = sock;
    sock->on_event = _on_stream_data;
    sock->parent = ctx;
    return sock;
}

void stream_socket_read(struct stream_socket_t *self, event_callback on_data, struct buffer_t buf, struct event_listener_t *listener)
{
    memcpy(&(self->buf), &buf, sizeof(struct buffer_t));
    self->parent_callback = on_data;
    stream_socket_handle(self, listener, EV_IN);
}

const ssize_t stream_socket_send(struct stream_socket_t *self, const char *buf, const size_t len, struct event_listener_t *listener)
{
    // const ssize_t sent_len = send(self->ident, buf, len, 0);
    // stream_socket_handle(self, listener, EV_OUT);
    return 0;
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
