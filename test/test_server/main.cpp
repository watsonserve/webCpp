#include "MsgServer.hpp"

#define THREAD_POOL_SIZ 8
#define FD_LIMIT 1024
#define EVENT_LIST_LENGTH 1019
#define PORT 7070

using namespace G;

void onConnect(void* ctx, SOCKET fd, sock_addr_t *addr)
{
    PresentationLayer *ioHandler;
    G::EventListener *listener = (G::EventListener *)ctx;
    ioHandler = new PresentationLayer(addr->addr, addr->len);
    G::IOStream::newInstance(listener, fd, FD_SOCKET, (G::IOHandler*)ioHandler);
}

int main()
{
    ThreadPool tpool;
    ThreadPool::init(tpool, THREAD_POOL_SIZ);
    EventListener &eventListener = EventListener::getInstance(&tpool, EVENT_LIST_LENGTH);
    listen_event(&eventListener);

    SOCKET sockfd = TCPsetup(PORT);
    acceptor(sockfd, FD_LIMIT, onConnect, &eventListener);
    G::IOStream::clean();

    return 0;
}
