#ifndef _GUDPSERVER_HPP_
#define _GUDPSERVER_HPP_

#include "G/net/Server.hpp"

namespace G {

    class UDPServer: public G::Server
    {
    public:
        UDPServer();
        virtual ~UDPServer();
        virtual int service(G::IOEvents *, int max);
    };

}

#endif