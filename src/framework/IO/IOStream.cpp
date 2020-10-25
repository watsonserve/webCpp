#include "G/io/IOStream.hpp"

std::map<void *, G::IOStream *> G::IOStream::streams;
/**** 私有静态方法 ****/

// 销毁一个stream，被异步调用
void G::IOStream::destroy(struct event_t &ev)
{
    delete (G::IOStream *)(ev.context);
    G::IOStream::streams.erase(ev.context);
}

/**** 公有静态方法 ****/

// 初始化一个实例
void G::IOStream::newInstance(G::EventListener *listener, int fd, FdType type, G::IOHandler *handler)
{
    G::IOStream *stream;
    stream = new G::IOStream(listener, fd, type, handler);
    G::IOStream::streams[stream] = stream;
}

// 析构所有实例
void G::IOStream::clean()
{
    size_t i, siz;
    std::map<void *, G::IOStream *>::iterator it = G::IOStream::streams.begin();
    siz = G::IOStream::streams.size();
    for(i = 0; i < siz; i++)
    {
        delete it->second;
        G::IOStream::streams.erase(it->first);
        it++;
    }
}

/**** 私有类方法 ****/

G::IOStream::IOStream(G::EventListener *listener, int fd, FdType type, G::IOHandler *handler)
{
    int fl;

    this->listener = listener;
    this->handler = handler;
    this->type = type;

    fl = fcntl(fd, F_GETFL, 0);
    fcntl(fd, F_SETFL, fl | O_NONBLOCK);

    i_event.ident = fd;
    i_event.event_type = EV_IN;
    i_event.context = this;
    i_event.function = G::IOStream::onData;
    this->setCacheFd(fd, type);

    o_event.ident = -1;
    o_event.event_type = EV_OUT;
    o_event.context = this;
    o_event.function = G::IOStream::onData;

    listener->emit(OPT_ADD, &i_event);
}

void G::IOStream::_close()
{
    if (-1 != o_event.ident)
    {
        listener->emit(OPT_DEL, &o_event);
        o_event.ident = -1;
    }
    if (-1 == i_event.ident)
    {
        return;
    }
    listener->emit(OPT_DEL, &i_event);
    ::close(i_event.ident);
    i_event.ident = -1;
}

/**** 公有类方法 ****/

G::IOStream::~IOStream()
{
    this->_close();
}

void G::IOStream::close()
{
    struct event_t event;

    shutdown(i_event.ident, SHUT_RDWR);
    this->_close();

    event.ident = -1;
    event.context = this;
    event.event_type = EV_ETC;
    event.function = G::IOStream::destroy;
    listener->emit(OPT_EXE, &event);
}
