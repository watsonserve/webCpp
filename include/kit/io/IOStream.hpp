#ifndef _G_IOSTREAM_HPP_
#define _G_IOSTREAM_HPP_

extern "C"
{
    #include <errno.h>
    #include <sys/socket.h>
    #include "io/io.h"
}

#include "event/EventListener.hpp"
#include "io/IOHandler.hpp"
#include "io/StreamCache.hpp"

namespace G
{
    class IOStream : public StreamCache
    {
        enum fd_type type;
        // lowest 1 closed
        int flag;

        std::string writeBuf;

        struct event_t i_event;
        struct event_t o_event;
        G::IOHandler *handler;
        G::EventListener *listener;

        static std::map<void *, G::IOStream *> streams;

        static void onWrittable(G::IOStream *, struct event_t &);
        static void onData(struct event_t &);
        static void onIn(G::IOStream *);
        static void destroy(struct event_t &);
        IOStream(G::EventListener *, int, FdType, G::IOHandler *);

        void _close();
    public:
        virtual ~IOStream();
        static void newInstance(G::EventListener *, int, FdType, G::IOHandler *);
        static void clean();
        void close();
        // ssize_t read(char *, ssize_t) override;
        void write(std::string &);
        void write(const char *, ssize_t);
    };
}

#endif
