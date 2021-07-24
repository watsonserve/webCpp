#ifndef _STREAM_SOCKET_H_
#define _STREAM_SOCKET_H_

#include <stdio.h>
#include <string.h>
#include "assert.h"
#include "net/net_base.h"
#include "kit.h"

struct buffer_t
{
    size_t siz;
    char *zone;
};

struct stream_socket_t;

typedef void (*callback_func)(struct stream_socket_t *, struct buffer_t);

#ifndef _STREAM_SOCKET_FIELDS_
#define _STREAM_SOCKET_FIELDS_ \
    _EVENT_FIELDS_ \
    struct sock_addr addr; \
    void *parent; \
    callback_func parent_callback; \
    struct buffer_t buf;
#endif

/**
 * {
 *      int64_t ident;
 *      void *self;
 *      event_callback on_event;
 *      event_type_t event_type;
 *      int magic;
 *      struct sock_addr addr;
 *      void *parent;
 *      callback_func parent_callback;
 *      struct buffer_t buf;
 * }
 */
struct stream_socket_t
{
    _STREAM_SOCKET_FIELDS_
};

/**
 * construct
 * @param sock struct stream_socket_t *
 * @param fd SOCKET
 * @param addr struct sock_addr *
 * @param ctx void *
 * @return 成功返回sock 失败返回NULL
 */
struct stream_socket_t * new_stream_socket(struct stream_socket_t *, SOCKET, struct sock_addr *, void*);

/**
 * 异步recv
 * @param sock struct stream_socket_t *
 * @param on_data callback_func
 * @param buf struct buffer_t
 * @param event_listener struct event_listener_t *
 */
void stream_socket_read(struct stream_socket_t *, callback_func, struct buffer_t, struct event_listener_t *);

const ssize_t stream_socket_send(struct stream_socket_t *, const char *, const size_t, struct event_listener_t *);

void stream_socket_shutdown(struct stream_socket_t *, int);

void stream_socket_close(struct stream_socket_t *);

#endif
