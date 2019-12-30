#ifndef _LINK_H_
#define _LINK_H_

#include <stdlib.h>

typedef struct
{
    size_t count;
    size_t max;
    size_t unit_size;
    void *mem_pool;
    void *free;
    link_node_t *header;
    link_node_t *last;
} link_t;

typedef struct
{
    link_node_t *next;
} link_node_t;

/**
 * @params link_t* link_handle
 * @params size_t* unit_size
 * @params void*   mem_pool
 * @params size_t  mem_pool_size
 * @return 最大个数
 */
int link_init(link_t*, const size_t, void *, const size_t);

/**
 * @params link_t* link_handle
 * @params size_t* unit_size
 * @params void*   mem_pool
 * @params size_t  mem_pool_size
 * @return 最大个数
 */
int queue_push(link_t *, void*);
int queue_pop(link_t *, void*);

#endif
