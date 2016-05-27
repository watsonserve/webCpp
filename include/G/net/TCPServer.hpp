#ifndef _GTCPSERVER_HPP_
#define _GTCPSERVER_HPP_

#include "G/net/Server.hpp"

namespace G {

    class TCPServer: public G::Server
    {
        virtual int service(G::IOEvents *, int max);
        virtual int serviceSafe(G::IOEvents *, int max);
    public:
        TCPServer();
        virtual ~TCPServer();
        virtual int initPool(int, int, int);
        int service(G::IOEvents *, int max, int sslFlag);
        virtual int setCert(const char *);
        virtual int setKey(const char *);
    };

}

#endif