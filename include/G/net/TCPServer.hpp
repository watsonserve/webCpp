#ifndef _GTCPSERVER_HPP_
#define _GTCPSERVER_HPP_

#include "G/net/StreamServer.hpp"

namespace G {

    class TCPServer: public G::StreamServer
    {
        unsigned short port;
    public:
        TCPServer();
        virtual ~TCPServer() override;
        int setPort(unsigned short);
        int setCert(const char *);
        int setKey(const char *);
        SOCKET initSocket() override;
    };

}

#endif
