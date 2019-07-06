#include <stdio.h>
#include <unistd.h>
#include <queue>
#include "G/ThreadPool.hpp"

struct context_t
{
    int no;
    int *intp;
};

class Exe : public G::Exeable
{
    public:
        int id;

        Exe() {};
        Exe(const Exe &);
        virtual ~Exe();
};

Exe::Exe(const Exe &exe)
{
    struct context_t *ctx = (struct context_t *)exe.context;
    printf("copy & %d\n", ctx->no);
    this->id = exe.id;
    this->context = exe.context;
    this->function = exe.function;
}

Exe::~Exe()
{
    struct context_t *ctx = (struct context_t *)this->context;
    printf("~ %d\n", ctx->no);
}

void func(G::Exeable *args)
{
    Exe *exe = (Exe *)args;
    struct context_t *ctx;
    ctx = (struct context_t *)args->context;
    printf("addr: %lX, id: %d, no: %d, i: %d\n", (int64_t)args, exe->id, ctx->no, *(ctx->intp));
    sleep(1);
}

void testQueue()
{
    struct context_t ctx;
    Exe task;
    std::queue<Exe> mq;

    ctx.no = -1;
    task.context = &ctx;
    printf("task addr: %lX\n", (int64_t)&task);
    mq.push(task);
    Exe &front = mq.front();
    printf("task addr: %lX\n", (int64_t)&front);
}

void main1()
{
    int i;
    G::ThreadPool tpool;
    Exe task;
    struct context_t ctx[4];

    i = G::ThreadPool::init(tpool, 2);
    if (i) {
        return;
    }

    task.function = func;
    for (i = 0; i < 4; i++)
    {
        ctx[i].no = i;
        ctx[i].intp = &i;
        task.id = i + 10;

        task.context = ctx + i;
        tpool.call(task);
    }
    sleep(3);
}

int main()
{
    // testQueue();
    main1();
    sleep(2);
    return 0;
}