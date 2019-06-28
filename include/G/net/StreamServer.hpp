#ifndef _STREAMSERVER_HPP_
#define _STREAMSERVER_HPP_

#include "G/net/Server.hpp"

extern "C"
{
    #include "G/net/Gnet.h"
}

namespace G {

    class StreamServer: public G::Server
    {
    public:
        void init();
        StreamServer();
        virtual ~StreamServer() =0;
        virtual int service(G::IOEvents *, int) override;
    };

}

#endif
