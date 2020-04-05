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
        G::EventListener *listener;
        void onConnect(SOCKET, struct sockaddr, socklen_t);
    protected:
        virtual G::IOHandler* handleGenerator(struct sockaddr, socklen_t) =0;
    public:
        StreamServer(G::EventListener *);
        StreamServer(SOCKET, G::EventListener *);
        virtual int service(int) override;
        virtual ~StreamServer();
    };

}

#endif
