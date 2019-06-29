#include <stdio.h>
#include <unistd.h>
#include <queue>
#include "G/ThreadPool.hpp"

struct context_t
{
    int no;
    int *intp;
};

void func(G::Exeable *args)
{
    struct context_t *ctx;
    ctx = (struct context_t *)args->context;
    printf("addr: %lX, no: %d, i: %d\n", (int64_t)args, ctx->no, *(ctx->intp));
}

int main()
{
    int i;
    G::ThreadPool tpool;
    G::Event task;
    struct context_t ctx[4];
    std::queue<G::Event> mq;

    printf("task addr: %lX\n", (int64_t)&task);
    mq.push(task);
    G::Event &front = mq.front();
    printf("task addr: %lX\n", (int64_t)&front);

    i = G::ThreadPool::init(tpool, 2);
    if (i) {
        return 1;
    }

    task.function = func;
    for (i = 0; i < 4; i++)
    {
        ctx[i].no = i;
        ctx[i].intp = &i;

        task.context = ctx + i;
        tpool.call(task);
    }
    sleep(2);
    return 0;
}