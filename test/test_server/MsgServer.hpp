#ifndef _MSGSERVER_HPP_
#define _MSGSERVER_HPP_

extern "C"
{
    #include "G/net/Gnet.h"
    #include "G/kit.h"
}

#include "G/ThreadPool.hpp"
#include "G/event/EventListener.hpp"
#include "G/net/StreamServer.hpp"
#include "G/io/IOHandler.hpp"

class PresentationLayer: virtual public G::IOHandler
{
public:
    PresentationLayer(struct sockaddr, socklen_t);
    virtual ~PresentationLayer();

    virtual void onOpen(G::IOStream *) override;
    virtual void onError(G::IOStream *, int) override;
    virtual void onClose(G::IOStream *) override;
    virtual void onData(G::IOStream *) override;
    virtual void onWritten(G::IOStream *) override;
};

#endif
