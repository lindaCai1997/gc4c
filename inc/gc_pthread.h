#ifndef _GC_PTHREAD_H_
#define _GC_PTHREAD_H_

#include <pthread.h>
#include "linkList.h"

#define pthread_create(thread, attr, start_routine, arg) gc_pthread_create(thread, attr, start_routine, arg)
#define pthread_join(thread, retval) gc_pthread_join(thread, retval)

static llNode* head = NULL;

int gc_pthread_join(pthread_t thread, void **retval);
int gc_pthread_create(pthread_t *thread, const pthread_attr_t *attr,
                           void *(*start_routine) (void *), void *arg);

#endif
