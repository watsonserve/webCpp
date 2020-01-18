#include "G/io/IOHub.hpp"

G::IOHub::IOHub(G::EventListener *listener)
{
    this->listener = listener;
}

G::IOHub::~IOHub()
{
    size_t i, siz;
    std::map<int, G::IOStream *>::iterator it = streams.begin();
    siz = streams.size();
    for(i = 0; i < siz; i++)
    {
        delete it->second;
        streams[it->first] = nullptr;
        it++;
    }
}

void G::IOHub::listen(int fd, G::IOHandler *handler)
{
    G::IOStream *stream = streams[fd];
    if (nullptr == stream)
    {
        stream = new G::IOStream(listener, handler);
        streams[fd] = stream;
    }
    stream->setFd(fd, FD_SOCKET);
}
