#ifndef _G_KIT_H_
#define _G_KIT_H_

#include "G/event/event.h"

struct event_listener_t {};

struct thread_pool_t {};

struct thread_pool_t * thread_pool_create(const int);

struct event_listener_t * event_listener_init(struct thread_pool_t *, int);

void listen_event(struct event_listener_t *);

int emit_event(struct event_listener_t *, event_opt_t, struct event_t *);

#endif
