#ifndef _MSGSERVER_HPP_
#define _MSGSERVER_HPP_

#include "G/ThreadPool.hpp"
#include "G/event/EventListener.hpp"
#include "G/net/TCPServer.hpp"
#include "G/net/Protocoler.hpp"

using namespace G;

class MsgServer: virtual public TCPServer, virtual public Protocoler
{
    char buf[BUFSIZ];
protected:
    virtual void onData(int fd, event_type_t event_type) override;
public:
    MsgServer(EventListener *, unsigned int);
    virtual ~MsgServer();
    int service(int);
};

#endif
