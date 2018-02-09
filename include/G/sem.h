//
//  sem.h
//  GHTTPd
//
//  Created by wangxingzhuo on 09/02/2018.
//  Copyright © 2018 watsserve. All rights reserved.
//

#ifndef _SEM_H_
#define _SEM_H_

#if defined(__APPLE__) || defined (__MACOSX__) || defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__) || defined(__bsdi__)

#include <errno.h>
#include <dispatch/dispatch.h>

typedef dispatch_semaphore_t sem_t;

int init_sem(sem_t*, int, int);
int wait_sem(sem_t*);
int post_sem(sem_t*);

#else
#include <semaphore.h>

#define init_sem sem_init
#define wait_sem sem_wait
#define post_sem sem_post

#endif

#endif /* sem_h */
