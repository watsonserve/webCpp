#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <iostream>
#include "G/Aio.hpp"
#include "G/StreamIO.hpp"
#include "G/IOHandle.hpp"
#include "G/IOEvents.hpp"

using namespace G;

class Async : public IOEvents
{
	int num;

public:
    Async() {
    	this->num = 0;
    };
    virtual ~Async() {};
    virtual void onConnect(StreamIO *in) {
        printf("get File");
    };
    virtual void onData(StreamIO *in)
    {
        printf("onData\n");
	while(!in->isEmpty())
	{
            printf("%X %s\n", ++(this->num), in->gets(LF).c_str());
	}
    };
    virtual void onError(StreamIO *in) {};
    virtual void onClose(StreamIO *in) {};
};

int main()
{
	int fd;
	char buf[BUFSIZ];
	StreamIO streamIO;
	Async ioEvents;
	struct aioinit ai;

	ai.aio_num = 8;
	ai.aio_threads = 4;

	Aio::aioInit(&ai);

	fd = open("main.cpp", O_RDONLY);
	if (-1 == fd) {
		return 1;
	}
	
	StreamIO::init(&streamIO, &ioEvents, buf, BUFSIZ);
	streamIO.setFd(fd, G::FILE);
	streamIO.listen();
	sleep(1);
	std::cout << std::endl << "over!\n";
	return 0;
}
