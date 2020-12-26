#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include "http/http_srv.h"

#define THREAD_POOL_SIZ 8
#define FD_LIMIT 1024
#define EVENT_LIST_LENGTH 1019
#define PORT 7070

void handle_http_req(struct http_context_t *ctx)
{
    struct http_req_t *req;
    char sess[32];
    struct cookies_t *cookies;
    
    req = ctx->req;
    cookies = http_req_get_header(req, "cookie");
    http_cookies_get("sess", sess, 32);
    load_sess(sess, 32, handle_sess, ctx);
}

void handle_sess(struct http_context_t *ctx)
{

}

int main()
{
    int err;
    struct thread_pool_t *tpool;
    struct event_listener_t *eventListener;

    tpool = thread_pool_create(THREAD_POOL_SIZ);
    eventListener = event_listener_init(tpool, EVENT_LIST_LENGTH);
    listen_event(eventListener);

    stream_socket_set_listener(eventListener);
    err = tcp_service(PORT, FD_LIMIT, handle_http_req, eventListener);
    errno = err;
    perror("srv exit");
    return err;
}
