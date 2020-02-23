#ifndef _G_IOSTREAM_HPP_
#define _G_IOSTREAM_HPP_

extern "C"
{
    #include <errno.h>
    #include <sys/socket.h>
    #include "G/io/io.h"
}

#include "G/event/Event.hpp"
#include "G/event/EventListener.hpp"
#include "G/io/IOHandler.hpp"
#include "G/io/StreamCache.hpp"

namespace G
{
    class IOStream : protected StreamCache
    {
        enum fd_type type;

        std::string writeBuf;

        G::Event i_event;
        G::Event o_event;
        G::IOHandler *handler;
        G::EventListener *listener;

        static void onWrittable(G::IOStream *, G::Event &);
        static void onData(G::Event &);
        static void onIn(G::IOStream *);
    public:
        IOStream(G::EventListener *, IOHandler *);
        virtual ~IOStream();
        void setFd(int, enum fd_type);
        void close();
        // ssize_t read(char *, ssize_t) override;
        void write(std::string &);
        void write(const char *, size_t);
    };
}

#endif
