#include "G/io/IOStream.hpp"

#ifdef __LINUX__

void G::IOStream::write(std::string &str)
{
    this->write(str.c_str(), str.length());
}

void G::IOStream::write(const char *str, ssize_t len)
{
    int fd, written_len;

    written_len = 0;
    fd = i_event.ident;

    // 缓存区是空的
    if (!writeBuf.length())
    {
        // 尝试写
        written_len = putout(fd, this->type, str, len);
    }
    // 没写完
    if (written_len < len)
    {
        // 放入缓存区
        this->writeBuf.append(str + written_len, len - written_len);
        o_event.ident = fd;
        // 等待可写事件
        listener->emit(OPT_ADD, &o_event);
        return;
    }
    // 提醒已写完
    // listener->emit(OPT_ADD, &o_event);
}

/**** 静态 ****/

void G::IOStream::onWrittable(G::IOStream *ioStream, G::Event &ev)
{
    int fd;
    ssize_t siz, len;

    fd = ev.ident;
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
        ioStream->o_event.ident = -1;
        ioStream->handler->onWritten(ioStream);
        return;
    }
    // 等待下次可写入事件
    ioStream->listener->emit(OPT_ADD, &ioStream->o_event);
}

void G::IOStream::onIn(G::IOStream *ioStream)
{
    int err;
    // 可读数据量为0异常
    if (ioStream->i_event.buf_size < 1)
    {
        ioStream->close();
        return;
    }
    err = ioStream->in_cache(ioStream->i_event.buf_size);
    switch (err)
    {
        case 0:
            ioStream->handler->onData(ioStream);
            break;
        case EBADF:
        case ECONNRESET:
            // The argument socket is an invalid descriptor.
            // The connection is closed by the peer during a receive attempt on a socket.
            ioStream->handler->onClose(ioStream);
            ioStream->close();
            break;
        default:
            ioStream->handler->onError(ioStream, err);
    }
    // 等下次
    if (0 <= ioStream->i_event.ident)
    {
        ioStream->listener->emit(OPT_ADD, &ioStream->i_event);
    }
}

void G::IOStream::onData(G::Event &ev)
{
    G::IOStream *ioStream = (G::IOStream *)(ev.context);

    switch ((uint32_t)ev.event_type)
    {
        case EV_ERR:
            ioStream->handler->onError(ioStream, ioStream->i_event.buf_size);
            return;
        case EV_IN:
            G::IOStream::onIn(ioStream);
            return;
        case EV_OUT:
            return;
        default:
            break;
    }
}

#endif
