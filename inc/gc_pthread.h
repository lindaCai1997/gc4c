#ifndef _GC_PTHREAD_H_
#define _GC_PTHREAD_H_


// #define pthread_create(thread, attr, start_routine, arg) gc_pthread_create(thread, attr, start_routine, arg)
#define pthread_join(thread, retval) gc_pthread_join(thread, retval)

llNode* pthread_ll_head = NULL;

#include <pthread.h>
#include "linkedList.h"

int gc_pthread_join(pthread_t thread, void **retval);
// int gc_pthread_create(pthread_t *thread, const pthread_attr_t *attr,
                           void *(*start_routine) (void *), void *arg);
// void gc_pthread_add_thread(long threadID, long stack_top, long stack_bottom);

#endif
