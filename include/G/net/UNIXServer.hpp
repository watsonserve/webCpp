#ifndef _GUNIXSERVER_HPP_
#define _GUNIXSERVER_HPP_

#include "G/net/Server.hpp"

namespace G {

    class UNIXServer: public G::Server
    {
        virtual int service(G::IOEvents *, int max);
    public:
        TCPServer();
        virtual ~TCPServer();
        virtual int initPool(int, int, int);
        int setPath(char *);
        int service(G::IOEvents *, int max, int sslFlag);
    };

}

#endif
