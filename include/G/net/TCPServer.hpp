#ifndef _GTCPSERVER_HPP_
#define _GTCPSERVER_HPP_

#include "G/net/Server.hpp"

namespace G {

    class TCPServer: public G::Server
    {
    public:
        TCPServer();
        virtual ~TCPServer() override;
        int setPort(int);
        int setCert(const char *);
        int setKey(const char *);
        SOCKET initSocket() override;
    };

}

#endif