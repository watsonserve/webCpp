#include "MsgServer.hpp"

#define THREAD_POOL_SIZ 8
#define FD_LIMIT 1024
#define EVENT_LIST_LENGTH 1019
#define PORT 7070

void transition(const int fd, enum fd_type type, G::EventListener *listener, void *ioHandler)
{
    G::IOStream::newInstance(listener, fd, FD_SOCKET, (G::IOHandler*)ioHandler);
}

void onConnect(void* ctx, SOCKET fd, sock_addr_t *addr)
{
    PresentationLayer *ioHandler;
    G::EventListener *listener = (G::EventListener *)ctx;
    ioHandler = new PresentationLayer(addr->addr, addr->len);
    transition(fd, FD_SOCKET, listener, (G::IOHandler*)ioHandler);
}

int main()
{
    int err;
    thread_pool_t tpool;
    event_listener_t eventListener;

    tpool = thread_pool_create(THREAD_POOL_SIZ);
    eventListener = event_listener_init(tpool, EVENT_LIST_LENGTH);
    listen_event(eventListener);

    err = tcp_service(PORT, FD_LIMIT, onConnect, eventListener);
    if (err)
        perror("tcp service error");
    G::IOStream::clean();

    return 0;
}
