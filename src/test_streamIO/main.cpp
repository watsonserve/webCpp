#include <stdio.h>
#include <iostream>
#include "G/StreamIO.hpp"
#include "G/IOHandle.hpp"
#include "G/IOEvents.hpp"

using namespace G;

class Async : public IOEvents
{
public:
    Async() {};
    virtual ~Async() {};
    virtual void onConnect(StreamIO *in) {};
    virtual void onData(StreamIO *in)
    {
    	std::cout << in->gets(LF);
    };
    virtual void onError(StreamIO *in) {};
    virtual void onClose(StreamIO *in) {};
};

int main()
{
	char buf[BUFSIZ];
	StreamIO streamIO;
	Async ioEvents;

	StreamIO::init(&streamIO, &ioEvents, buf, BUFSIZ);
	streamIO.setFd(0, UNIX_SOCKET);
	streamIO.listen();
	return 0;
}