#ifndef _MSGSERVER_HPP_
#define _MSGSERVER_HPP_

#include "G/ThreadPool.hpp"
#include "G/event/EventListener.hpp"
#include "G/net/StreamServer.hpp"
#include "G/net/Gnet.h"
#include "G/io/IOHandler.hpp"

using namespace G;

class MsgServer: virtual public StreamServer, virtual public IOHandler
{
public:
    MsgServer(EventListener *, unsigned short);
    virtual ~MsgServer();
    int service(int);

    virtual void onOpen(IOStream *) override;
    virtual void onError(IOStream *, int) override;
    virtual void onClose(IOStream *) override;
    virtual void onData(IOStream *) override;
    virtual void onWritten(IOStream *) override;
};

#endif
