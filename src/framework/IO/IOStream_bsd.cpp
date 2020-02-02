#include "G/io/IOStream.hpp"

#ifdef __BSD__

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

inline int min(int foo, int bar)
{
    return foo < bar ? foo : bar;
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
    this->close();
}

void G::IOStream::setFd(int fd, G::FdType type)
{
    int fl;

    this->type = type;
    fl = fcntl(fd, F_GETFL, 0);
    fcntl(fd, F_SETFL, fl | O_NONBLOCK);

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

void G::IOStream::close()
{
    if (-1 != o_event.ident)
    {
        listener->emit(OPT_DEL, &o_event);
    }
    if (-1 != i_event.ident)
    {
        listener->emit(OPT_DEL, &i_event);
        ::close(i_event.ident);
    }
    i_event.ident = -1;
    o_event.ident = -1;
}

ssize_t G::IOStream::read(char *buf, ssize_t size)
{
    ssize_t siz;

    siz = min(i_event.buf_size, size);
    switch (type)
    {
        case G::FdType::FD_SOCKET:
            siz = recv(i_event.ident, buf, siz, 0);
            break;
        default:
            siz = ::read(i_event.ident, buf, siz);
    }
    if (-1 == siz)
    {
        if (EAGAIN == errno) return 0;
    }
    return siz;
}

void G::IOStream::write(std::string &str)
{
    this->write(str.c_str(), str.length());
}

void G::IOStream::write(const char *str, size_t len)
{
    this->writeBuf.append(str, len);
    o_event.ident = i_event.ident;
    listener->emit(OPT_ADD, &o_event);
}

// 静态
void G::IOStream::onData(G::Event &ev)
{
    int fd;
    ssize_t siz, len;
    G::event_type_t event_type;
    G::IOStream *ioStream;

    ioStream = (G::IOStream *)(ev.context);
    fd = ev.ident;

    switch ((uint32_t)ev.event_type)
    {
        case EV_ERR:
            ioStream->handler->onError(ioStream, 0);
            return;
        case EV_IN:
            if (0 < ioStream->i_event.buf_size)
            {
                ioStream->handler->onData(ioStream);
            }
            return;
        case EV_OUT:
            // 可写数据量
            siz = min(ioStream->writeBuf.length(), ev.buf_size);
            if (!siz) return;
            // 写入
            len = putout(fd, ioStream->type, ioStream->writeBuf.c_str(), siz);
            // 写失败
            if (-1 == len)
            {
                ioStream->handler->onError(ioStream, errno);
                return;
            }
            ioStream->writeBuf.erase(0, len);
            // 写完
            if (!ioStream->writeBuf.length())
            {
                ioStream->listener->emit(OPT_DEL, &ioStream->o_event);
                ioStream->o_event.ident = -1;
                ioStream->handler->onWritten(ioStream);
            }
            return;
        default:
            break;
    }
}

#endif
