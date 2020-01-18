#ifndef _GSOCKET_HPP_
#define _GSOCKET_HPP_

extern "C"
{
    #include <unistd.h>
    #include "G/net/Gnet.h"
}

namespace G
{

    class Socket
    {
    protected:
        SOCKET sockfd;
        virtual void initSocket();
    };

}

#endif
