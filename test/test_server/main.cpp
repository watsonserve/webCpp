#include "MsgServer.hpp"

#define THREAD_POOL_SIZ 8
#define FD_LIMIT 1024
#define EVENT_LIST_LENGTH 1019
#define PORT 7070

void onConnect(void* ctx, SOCKET fd, sock_addr_t *addr)
{
    PresentationLayer *ioHandler;
    ioHandler = new PresentationLayer(addr->addr, addr->len);
    G::IOStream::newInstance(listener, fd, FD_SOCKET, (G::IOHandler*)ioHandler);
}

int main()
{
    int err;
    struct thread_pool_t *tpool;
    struct event_listener_t *eventListener;

    tpool = thread_pool_create(THREAD_POOL_SIZ);
    eventListener = event_listener_init(tpool, EVENT_LIST_LENGTH);
    listen_event(eventListener);

    err = tcp_service(PORT, FD_LIMIT, onConnect, eventListener);
    if (err) perror("tcp service error");

    return 0;
}
