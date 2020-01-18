extern "C"
{
    #include <errno.h>
    #include <sys/socket.h>
}
#include "G/io/IOStream.hpp"

static ssize_t putout(int fd, G::FdType type, const char *buf, ssize_t len)
{
    switch (type)
    {
        case G::FdType::FD_SOCKET:
            return send(fd, buf, len, 0);
        default:
            return write(fd, buf, len);
    }
}

G::IOStream::IOStream(G::EventListener *listener, G::IOHandler *handler)
{
    this->listener = listener;
    this->handler = handler;
    i_event.ident = -1;
    o_event.ident = -1;
}

G::IOStream::~IOStream()
{
    if (-1 != i_event.ident)
    {
        listener->emit(OPT_DEL, &i_event);
    }
    if (-1 != o_event.ident)
    {
        listener->emit(OPT_DEL, &o_event);
    }
}

void G::IOStream::setFd(int fd, G::FdType type)
{
    this->type = type;

    i_event.ident = fd;
    i_event.event_type = EV_IN;
    i_event.context = this;
    i_event.function = G::IOStream::onData;

    o_event.ident = fd;
    o_event.event_type = EV_OUT;
    o_event.context = this;
    o_event.function = G::IOStream::onData;

    listener->emit(OPT_ADD, &i_event);
}

ssize_t G::IOStream::read(char *buf, ssize_t size)
{
    switch (type)
    {
        case G::FdType::FD_SOCKET:
            return recv(i_event.ident, buf, size, 0);
        default:
            return ::read(i_event.ident, buf, size);
    }
}

void G::IOStream::write(std::string &str)
{
    this->writeBuf = str;
    o_event.event_type = EV_OUT;
#ifdef __LINUX__
    listener->emit(OPT_ADD, &o_event);
#endif
#ifdef __BSD__
    listener->emit(OPT_ADD, &o_event);
#endif
}

// 静态
void G::IOStream::onData(G::Event &ev)
{
    int fd;
    ssize_t len;
    G::event_type_t event_type;
    G::IOStream *ioStream;

    ioStream = (G::IOStream *)(ev.context);
    fd = ev.ident;

    switch (ev.event_type)
    {
        case EV_ERR:
            ioStream->handler->onError(ioStream, 0);
            break;
        case EV_IN:
            ioStream->handler->onData(ioStream);
            break;
        case EV_OUT:
            len = putout(fd, ioStream->type, ioStream->writeBuf.c_str(), ioStream->writeBuf.length());
            if (-1 == len)
            {
                ioStream->handler->onError(ioStream, errno);
                break;
            }
            // @TODO: len < ioStream->writeBuf.length()
            ioStream->handler->onWritten(ioStream, len);
            break;
        default:
            break;
    }
}
