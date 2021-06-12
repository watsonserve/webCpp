#ifndef _HTTP_PROTO_HPP_
#define _HTTP_PROTO_HPP_

#include "G/net/StreamSocket.hpp"

namespace G
{
    class HttpProto : public G::StreamSocket {
        HttpProto(SOCKET fd);
        virtual ~HttpProto() override;

        virtual void onData();
        virtual void onSent();
        virtual void onClose();
    }
}

#endif
