#include <stdio.h>
#include <unistd.h>
#include <queue>
#include "G/ThreadPool.hpp"
#include "G/event/Event.hpp"

struct context_t
{
    int no;
    int *intp;
};

void func(G::Event *args)
{
    struct context_t *ctx;
    ctx = (struct context_t *)args->context;
    printf("addr: %llX, id: %llu, no: %d, intp: %d\n", (int64_t)args, args->ident, ctx->no, *(ctx->intp));
    sleep(1);
}

int main()
{
    int i;
    G::ThreadPool tpool;
    G::Event task;
    struct context_t ctx[4];

    i = G::ThreadPool::init(tpool, 2);
    if (i) {
        return 1;
    }

    task.function = func;
    for (i = 0; i < 4; i++)
    {
        ctx[i].no = i;
        ctx[i].intp = &i;
        task.ident = 1 << i;

        task.context = ctx + i;
        tpool.call(task);
    }
    sleep(3);
    return 0;
}