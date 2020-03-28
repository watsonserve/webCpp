#ifndef _STREAMSERVER_HPP_
#define _STREAMSERVER_HPP_

#include <map>
#include "G/event/Event.hpp"
#include "G/net/Server.hpp"
#include "G/event/EventListener.hpp"
#include "G/io/IOHandler.hpp"
#include "G/io/IOStream.hpp"

namespace G
{

    class StreamServer: public Server
    {
    // parent protected:
    //     SOCKET sockfd;
    //     virtual int _service(G::IOHandler *, int) =0;
        G::EventListener *listener;
        void listen(int, IOHandler *);
    protected:
        virtual int _service(G::IOHandler *, int) override;
    public:
        StreamServer(G::EventListener *);
        StreamServer(SOCKET, G::EventListener *);
        virtual ~StreamServer();
    };

}

#endif
