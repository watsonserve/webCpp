#ifndef _GHTTPDISPATCHER_HPP_
#define _GHTTPDISPATCHER_HPP_

#include <string>
#include <list>
#include "G/IOEvents.hpp"
#include "G/net/http/MiddleWare.hpp"

namespace G
{

    class HTTPDispatcher : virtual public IOEvents
    {
        std::list<G::MiddleHandle> process;
        HTTPRequest *requests;
        HTTPResponse *responses;
    public:
        HTTPDispatcher();
        virtual ~HTTPDispatcher();
        virtual int init(int max);
        virtual void onConnect(StreamIO *) {};
        virtual void onData(StreamIO *);
        virtual void onComplete(StreamIO *) {};
        virtual void onError(StreamIO *);
        virtual void onClose(StreamIO *);
        virtual int use(G::MiddleWare* middleware);
        virtual int use(G::MiddleWareFunc middleware);
    };

}

#endif
