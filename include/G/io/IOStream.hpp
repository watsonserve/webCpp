#ifndef _G_IOSTREAM_HPP_
#define _G_IOSTREAM_HPP_

extern "C"
{
    #include <errno.h>
    #include <sys/socket.h>
}

#include "G/event/Event.hpp"
#include "G/event/EventListener.hpp"
#include "G/io/IOHandler.hpp"

namespace G
{
    typedef enum fd_type
    {
        FD_FILE,
        FD_SOCKET,
    } FdType;

    class IOStream
    {
        enum fd_type type;

        std::string writeBuf;

        G::Event i_event;
        G::Event o_event;
        G::IOHandler *handler;
        G::EventListener *listener;

        static void onData(G::Event &);
    public:
        IOStream(G::EventListener *, IOHandler *);
        virtual ~IOStream();
        void setFd(int, enum fd_type);
        void close();
        ssize_t read(char *, ssize_t);
        void write(std::string &);
        void write(const char *, size_t);
    };
}

#endif
