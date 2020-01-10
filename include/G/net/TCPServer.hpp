#ifndef _GTCPSERVER_HPP_
#define _GTCPSERVER_HPP_

#include "G/net/StreamServer.hpp"

namespace G {

    class TCPServer: virtual public G::StreamServer
    {
        unsigned short port;
    protected:
        SOCKET initSocket() override;
    public:
        TCPServer(G::EventListener *);
        int setPort(unsigned short);
        int setCert(const char *);
        int setKey(const char *);
    };

}

#endif
