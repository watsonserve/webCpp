#include "MsgServer.hpp"

#define THREAD_POOL_SIZ 8
#define FD_LIMIT 1024
#define EVENT_LIST_LENGTH 1019
#define PORT 7070

int main()
{
    int errno;
    thread_pool_t *tpool;
    event_listener_t *eventListener;

    // init a thread pool
    tpool = thread_pool_create(THREAD_POOL_SIZ);
    // init the IO event listener
    eventListener = event_listener_init(tpool, EVENT_LIST_LENGTH);
    // listen IO event
    listen_event(eventListener);

    // setup a tcp socket
    SOCKET sockfd = tcp_setup(PORT);
    if (-1 == sockfd) {
        perror("port linsten error");
        return 1;
    }
    // use http server handle the tcp socket
    errno = http_server(sockfd, FD_LIMIT, eventListener);
    if (errno)
        perror("http service error");

    return 0;
}
