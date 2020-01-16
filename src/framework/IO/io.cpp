extern "C" {
    #include <unistd.h>
}
#include "G/io/IO.hpp"

G::IO::IO(int fd)
{
    this->fd = fd;
}

G::IO::~IO()
{
    if (-1 == fd) return;
    ::close(fd);
}

void G::IO::close()
{
    ::close(fd);
    fd = -1;
}
