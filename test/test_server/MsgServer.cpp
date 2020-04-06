#include "MsgServer.hpp"

PresentationLayer::PresentationLayer(struct sockaddr_in addr, socklen_t len)
{}

void PresentationLayer::onError(G::IOStream *s, int e)
{
    printf("onError: %s\n", strerror(e));
}

void PresentationLayer::onClose(G::IOStream *stream)
{
    printf("onClose\n");
}

void PresentationLayer::onData(G::IOStream *stream)
{
    char buf[BUFSIZ];
    int len;

    len = stream->read(buf, BUFSIZ);
    if (len < 0)
    {
        printf("msgServer onData: %d exception: %s\n", errno, strerror(errno));
        stream->close();
    }
    if (len < 1)
    {
        printf("msgServer onData len < 1\n");
        return;
    }
    buf[len] = 0;
    printf("%s-------- over\n", buf);
    strcpy(buf, "HTTP/1.1 404 NOT FOUND\r\nContent-Length: 54\r\n\r\n<!DOCTYPE html><html><body>404 Not Found</body></html>\0");
    stream->write(buf, 101);
}

void PresentationLayer::onWritten(G::IOStream *stream)
{
    printf("written\n");
    char buf[BUFSIZ];
    int len;

    len = stream->read(buf, BUFSIZ);
    if (len < 0)
    {
        printf("msgServer onWritten debug: %s\n", strerror(errno));
        stream->close();
        return;
    }
    if (len)
    {
        printf("msgServer onWritten found: %s\n", buf);
    }
    // stream->close();
}
