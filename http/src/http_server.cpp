#include <string.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <map>
#include "net/net_base.h"
#include "G/io/handler_pool.h"
// #include "http/server.hpp"

// void HttpServer::onData(TCPSocket *sock, event_type_t event_type)
// {
//     int len;
//     char buf[BUFSIZ];
//     char header[] = "HTTP1.1 200 OK\r\nContent-Type: text/html;charset=utf-8\r\nContent-Length: 53\r\n\r\n";
//     char body[] = "<!DOCTYPE html><html><body>Hello world!</body></html>";

//     // printf("event: %lX, fd: %d\n\n", event_type, sock->fd);
//     len = sock->read(buf, BUFSIZ);
//     if (len < 1)
//     {
//         printf("exception: len = %d\n\n", len);
//         close(fd);
//         return;
//     }
//     buf[len] = 0;
//     len = strlen(header);
//     printf("%s\n--------\nover resp header len: %d\n", buf, len);

//     // response
//     strcpy(buf, header);
//     strcpy(buf + len, body);
//     send(fd, buf, len + strlen(body), 0);
//     close(fd);
// }

// int parse_http_rep_str(std::map<std::string, std::string> &ret, std::string &srcStr) {
//     std::string empty_line = "\r\n\r\n";
//     std::string crlf = "\r\n";
//     std::vector<std::string> header_wrapper, header;
//     auto body_start = split(header_wrapper, srcStr, empty_line, 1);
//     if (!header_wrapper.size())
//         return -1;
//     std::string str_header = header_wrapper[0];
//     split(header, str_header, crlf, unsigned int(-1));
// }


struct http_trans_t
{
    int gram;
};

struct http_handler
{
    _STREAM_SOCKET_FIELDS_
    struct http_trans_t *http_ctx;
};

void _http_on_data(struct stream_socket_t *sock, struct buffer_t buf) {
    handler_pool_t *aio_handler;
    struct http_handler *http_sock;
    struct http_trans_t *http_ctx;

    aio_handler = (handler_pool_t *)(sock->parent);
    http_sock = (struct http_handler *)get_stream_socket(aio_handler, sock->ident);
    http_ctx = http_sock->http_ctx;
    // ok = http_parse(http_ctx, buf, len)
    // if (!len)
    // {
    //     return;
    // }
    // if (ok) http_on_request(http_ctx)
    handler_pool_recv(aio_handler, sock->ident, _http_on_data, sock->buf);
}

void _http_on_connect(void* ctx, SOCKET fd, sock_addr_t *addr)
{
    struct http_handler *sock;
    handler_pool_t *aio_handler;

    aio_handler = (handler_pool_t *)ctx;
    sock = (struct http_handler *)handler_pool_handle(aio_handler, fd, addr);
    // @TODO sock->buf.zone = malloc(sock->buf.size)
    handler_pool_recv(aio_handler, fd, _http_on_data, sock->buf);
}

int http_server(SOCKET sockfd, int fd_limit, struct event_listener_t * event_listener)
{
    handler_pool_t *aio_handler = handler_pool(fd_limit, sizeof(struct http_handler), event_listener);
    return acceptor(sockfd, fd_limit, _http_on_connect, (void *)aio_handler);
}
