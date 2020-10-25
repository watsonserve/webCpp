#ifndef _G_KIT_H_
#define _G_KIT_H_

#include "G/event/event.h"

typedef void* thread_pool_t;

typedef void* event_listener_t;

thread_pool_t thread_pool_create(int);

event_listener_t event_listener_init(thread_pool_t, int);

void listen_event(event_listener_t);

int emit_event(event_listener_t, event_opt_t, struct event_t *);

#endif
