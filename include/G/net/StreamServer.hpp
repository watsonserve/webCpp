#ifndef _STREAMSERVER_HPP_
#define _STREAMSERVER_HPP_

#include "G/event/Event.hpp"
#include "G/net/Server.hpp"
#include "G/event/EventListener.hpp"
#include "G/io/IOHub.hpp"

namespace G
{

    class StreamServer: public Server, private IOHub
    {
    // parent protected:
    //     SOCKET sockfd;
    //     virtual int _service(G::IOHandler *, int) =0;
    protected:
        virtual int _service(G::IOHandler *, int) override;
        void setSocket(SOCKET);
    public:
        StreamServer(G::EventListener *);
        StreamServer(SOCKET, G::EventListener *);
    };

}

#endif
