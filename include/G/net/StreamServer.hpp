#ifndef _STREAMSERVER_HPP_
#define _STREAMSERVER_HPP_

extern "C"
{
    #include "G/net/Gnet.h"
}

#include "G/net/Server.hpp"
#include "G/event/EventListener.hpp"

namespace G {

    class StreamServer: public G::Server
    {
        G::EventListener *listener;
    public:
        void init(G::EventListener *listener);
        StreamServer();
        virtual ~StreamServer() =0;
        virtual int service(G::IOEvents *, int) override;
    };

}

#endif
