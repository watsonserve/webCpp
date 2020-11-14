#include "G/net/stream_socket.h"

static event_listener_t *listener;

void stream_socket_set_listener(event_listener_t *event_listener)
{
    listener = event_listener;
}

void _stream_socket_handle(struct stream_socket_t *socket, event_type_t event_type)
{
    struct event_t event;

    event.ident = socket->fd;
    event.event_type = event_type;
    event.context = socket;
    event.function = socket->onData;

    emit_event(listener, OPT_ADD, &event);
}

void stream_socket_listen(struct stream_socket_t *stream_sock)
{
    _stream_socket_handle(stream_sock, EV_IN);
}


const ssize_t stream_socket_read(struct stream_socket_t *self, char *buf, const size_t len)
{
    const size_t recv_len = recv(self->fd, buf, len, 0);
    if (-1 != recv_len)
        _stream_socket_handle(self, EV_IN);
    return recv_len;
}

const ssize_t stream_socket_send(struct stream_socket_t *self, const char *buf, const int len)
{
    const ssize_t sent_len = send(self->fd, buf, len, 0);
    _stream_socket_handle(self, EV_OUT);
    return sent_len;
}

void stream_socket_shutdown(struct stream_socket_t *self, int how)
{
    shutdown(self->fd, how);
}

void stream_socket_close(struct stream_socket_t *self)
{
    clean(self->fd);
    free(self);
}
