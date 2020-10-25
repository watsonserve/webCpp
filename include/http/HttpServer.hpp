#ifndef _HTTP_SERVER_HPP_
#define _HTTP_SERVER_HPP_

#include "G/net/UNIXServer.hpp"

class HTTPServer: public virtual G::UNIXServer, virtual G::Protocoler
{
protected:
    virtual void onData(int fd, event_type_t event_type) override;
public:
    HTTPServer();
    virtual ~HTTPServer() override;
    int service(int);
};

#endif
