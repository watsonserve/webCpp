extern "C" {
    #include "G/kit.h"
}
#include "G/event/EventListener.hpp"
#include "G/ThreadPool.hpp"

void listen_event(struct event_listener_t *listener)
{
    G::EventListener* l = (G::EventListener *)listener;
    l->listen();
}

struct event_listener_t * event_listener_init(void* tpool, int max)
{
    G::EventListener &retval = G::EventListener::getInstance((G::ThreadPool *)tpool, max);
    return (struct event_listener_t *)&retval;
}

int emit_event(struct event_listener_t *listener, event_opt_t opt, struct event_t *eventData)
{
    G::EventListener* l = (G::EventListener *)listener;
    return l->emit(opt, (struct event_t *)eventData);
}

struct thread_pool_t * thread_pool_create(const int max)
{
    G::ThreadPool *tpool = new G::ThreadPool();
    if (!G::ThreadPool::init(*tpool, max))
    {
        return (struct thread_pool_t *)tpool;
    }
    delete tpool;
    return nullptr;
}
