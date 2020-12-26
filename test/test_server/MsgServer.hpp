#ifndef _MSGSERVER_HPP_
#define _MSGSERVER_HPP_

extern "C"
{
    #include "G/net/net_base.h"
    #include "G/kit.h"
}

#include "G/io/IOStream.hpp"
#include "G/io/IOHandler.hpp"

class PresentationLayer: public G::IOHandler
{
public:
    PresentationLayer(struct sockaddr_in, socklen_t);

    virtual void onError(G::IOStream *, int) override;
    virtual void onClose(G::IOStream *) override;
    virtual void onData(G::IOStream *) override;
    virtual void onWritten(G::IOStream *) override;
};

#endif
