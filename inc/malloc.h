/*
 * malloc.h
 *
 * Header file for malloc functions
 *
 */
#ifndef _MALLOC_H_
#define _MALLOC_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stddef.h>
#include <signal.h>
#include "dataStructure.h" 
#include "mark_and_sweep.h"

#define malloc(size) gc_malloc(size)
#define realloc(ptr, size) gc_malloc(ptr, size)
#define calloc(nmemb, size) gc_calloc(nmemb, size)
#define free(ptr) gc_free(ptr)

int _CLEAN_FLAG;
void SIGNALHANDLER();
pthread_mutex_t _SIGNAL_MUTEX = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t _MALLOC_MUTEX = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t _SIGNAL_CV = PTHREAD_COND_INITIALIZER;


void gc_init();
void gc_destroy();
void* gc_malloc(size_t size);
void* gc_realloc(void* ptr, size_t size);
void gc_free(void* ptr);
void* gc_calloc(size_t nmemb, size_t size);
void gc_destroy();

#endif
