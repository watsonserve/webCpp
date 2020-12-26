extern "C"
{
    #include <stdio.h>
    #include <unistd.h>
    #include "http/http_srv.h"
}
#include "http/http_srv.hpp"

void G::HttpReq::recv_event(struct event_t ev)
{
    char buf[BUFSIZ];
    ssize_t len;

    G::HttpReq *req = (G::HttpReq *)(ev.context);
    if (nullptr == req)
    {
        close(ev.ident);
        return;
    }
    switch (ev.event_type)
    {
        case EV_IN:
            len = stream_socket_read(req, buf, BUFSIZ);
            printf("len: %ld:\n%s\n", len, buf);
        default:
            clean(req->sock.fd);
    }
}

G::HttpReq::HttpReq(SOCKET fd, struct sock_addr *addr)
{
    sock.fd = fd;
    sock.addr = *addr;
}

void G::HttpReq::handleHttpReq(struct event_listener_t *listener, SOCKET client_fd, sock_addr_t *addr)
{
    struct event_t event;

    event.context = new G::HttpReq(client_fd, addr);

    if (nullptr == event.context)
    {
        close(client_fd);
        return;
    }
    event.event_type = EV_IN;
    event.ident = client_fd;
    event.function = G::HttpReq::recv_event;

    emit_event(listener, OPT_ADD, &event);
}

void handle_http_req(struct event_listener_t *listener, SOCKET client_fd, struct sock_addr *addr)
{
    G::HttpReq::handleHttpReq(listener, client_fd, addr);
}
