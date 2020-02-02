#include "MsgServer.hpp"

using namespace G;

int main()
{
    ThreadPool tpool;
    ThreadPool::init(tpool, 8);
    EventListener &eventListener = EventListener::getInstance(&tpool, 8);
    eventListener.listen();
    MsgServer msgServer(&eventListener, 7070);

    pid_t pid = fork();
    msgServer.service(8);
    return 0;
}
