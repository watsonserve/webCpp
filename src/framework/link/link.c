#include "G/link.h"

int const link_init(link_t* this, const size_t unit_size, void* mem_pool, const size_t mem_pool_size)
{
    register int i;
    // 节点尺寸
    register size_t node_size, max;
    register link_node_t *p;

    node_size = sizeof(link_node_t) + unit_size;
    max = mem_pool_size / node_size;
    if (max < 1) {
        return 0;
    }

    this->count = 0;
    this->max = max;
    this->unit_size = unit_size;
    this->mem_pool = mem_pool;
    this->free = mem_pool;
    this->header = NULL;
    this->last = NULL;

    // 初始化空闲链表
    p = mem_pool;
    for (i = 1; i < max; i++)
    {
        p->next = p + node_size;
        p = p->next;
    }
    p->next = NULL;
    return max;
}

static void _stack_push(link_node_t **topp, link_node_t *node)
{
    node->next = *topp;
    *topp = node;
}

static link_node_t* _stack_pop(link_node_t **topp)
{
    register link_node_t *top;
    top = *topp;
    *topp = top->next;
    return top;
}

int queue_push(link_t * this, void* data)
{
    register link_node_t *last;

    // 没有内存空间嘞 >_<
    if (this->max <= this->count)
    {
        return -1;
    }
    // 取出第一个free节点
    last = _stack_pop(&this->free);
    last->next = NULL;
    // 拷贝数据
    memcpy(last + sizeof(link_node_t), data, this->unit_size);
    // 挂载
    if (0 == this->count)
    {
        this->header = last;
    }
    else
    {
        this->last->next = last;
    }
    // 移动last指针
    this->last = last;
    // 计数增加
    this->count++;
    return 0;
}

int queue_pop(link_t * this, void* dst)
{
    link_node_t *pop;

    // 空链表无法取出
    if (0 == this->count)
    {
        dst = NULL;
        return -1;
    }
    // 取第一个节点
    pop = _stack_pop(&this->header);
    // 拷贝数据
    memcpy(dst, pop + sizeof(link_node_t), this->unit_size);
    // 更新计数
    this->count--;
    if (0 == this->count)
    {
        this->last = NULL;
    }
    // 将卸载的节点压入空闲链表
    _stack_push(&this->free, pop);

    return 0;
}
