#ifndef _HTTP_SRV_HPP_
#define _HTTP_SRV_HPP_

extern "C"
{
    #include "G/net/stream_socket.h"
}

namespace G
{
    class HttpReq
    {
        struct stream_socket_t sock;
        static void recv_event(struct event_t ev);

        public:
            static void handleHttpReq(struct event_listener_t *, SOCKET, sock_addr_t *);
            HttpReq(SOCKET, struct sock_addr *);
            virtual ~HttpReq();
            void recv_event(struct event_t);
            struct stream_socket_t * getStreamSocket();
    };
}

#endif
