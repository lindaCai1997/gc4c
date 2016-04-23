//good lord I don't know if this is correct
/*c.c
 *
 * malloc.h implementation
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stddef.h>
#include <pthread.h>
#include "malloc.h"
#include "dataStructure.h" 
#include "mark_and_sweep.h"
#include "gc_thread.h"

#undef malloc
#undef calloc
#undef realloc
#undef free

void SIGNALHANDLER()
{
    fprintf(stderr, "I am thread: %d.  I will sleep for a while...\n", (int)pthread_self());
    pthread_mutex_lock(&_SIGNAL_MUTEX);
    while(_CLEAN_FLAG)
    {
        pthread_cond_wait(&_SIGNAL_CV, &_SIGNAL_MUTEX);
    }
    pthread_mutex_unlock(&_SIGNAL_MUTEX);
    fprintf(stderr, "I am thread: %d. I am awake!!!!\n", (int)pthread_self());
}

void* clean_helper()
{
    pthread_mutex_lock(&_SIGNAL_MUTEX);
    _CLEAN_FLAG = 1;
    pthread_mutex_unlock(&_SIGNAL_MUTEX);
    if(_pthread_ds != NULL)
    {
        Node* current = _pthread_ds->head;
        pthread_t calling_thread_PID = pthread_self();
        while(current != NULL)
        {
            pthread_t pid = (pthread_t) current->address;
            if(pid != calling_thread_PID) //put all other threads to sleep
                pthread_kill(pid, SIGUSR1); 
            current = current->next;
        }
    }
    mark_on_stack(_metaData);
	mark_on_heap(_metaData);
    sweep(_metaData);
    pthread_mutex_lock(&_SIGNAL_MUTEX);
    _CLEAN_FLAG = 0;
    pthread_cond_broadcast(&_SIGNAL_CV);
    pthread_mutex_unlock(&_SIGNAL_MUTEX);
    return NULL;
}

/*
 * should be called by one thread
 */
void gc_init()
{
    size_t i;
    char num[100];
    char again[100];
    for (k = 0; k < 100; k++){
        num[k] = 0;
        again[k] = 0;
    }
    register size_t j asm("r11");
    asm("movq %rbp, %r12\n\t"
        "popq %rbp\n\t"
        "movq %rbp, %r11\n\t"
        "movq %r12, %rbp");
    sprintf(num, "%zx", j);
    size_t k = 0;
    for (k = 0; k < strlen(num); k++){
        again[k] = num[k];
    }
    again[strlen(num)] = '\0';
    sscanf(again, "%zx", i);
    set_stack_bottom(i);
    _metaData = DataStructure_init();
}

/*
 * should be called by one thread
 * initiate a thread-safe gc
 */
void gc_init_r(){
    CLEAN_FLAG = 0;
    gc_init();
    gc_pthread_init();
    phtread_t* tid = (pthread_t*) malloc(sizeof(pthread_t));
    *tid = pthread_self();
    fprintf(stderr, "I am the main thread id: %d\n",(int)(*tid));
    Node_insert(_pthread_ds, (void*) tid, 0);
    signal(SIGUSR1, SIGNALHANDLER);
}

/*
 * should be called by one thread
 */
void gc_destroy()
{
     mark_all_on_stack(_metaData);
     sweep(_metaData);
     DataStructure_destroy(_metaData);
    //user calls this at the end of program
}

void* gc_malloc(size_t size){
    pthread_mutex_lock(&MALLOC_MUTEX);
    void* userData = malloc(size);
    Node_insert(_metaData, userData, size);
	clean_helper();
    pthread_mutex_unlock(&MALLOC_MUTEX);
    return userData;
}

void* gc_realloc(void* ptr, size_t size){
    if(ptr == NULL)
        return NULL;
    if(size == 0)
    {
        gc_free(ptr);
        return ptr;
    }
    Node* node = DataStructure_findNode(_metaData, ptr);
    size_t oldsize = node->size;
    size_t newsize = oldsize > size ? size : oldsize; 

    Node_remove(_metaData, ptr);

    void* newptr = realloc(ptr, size);
    if(newptr == NULL)
        return NULL;

    Node_insert(_metaData, newptr, newsize);

    return newptr;
}

void gc_free(void* ptr){
	if (ptr == NULL)
		return;
	else {
    	Node* node = (Node*)DataStructure_findNode(_metaData, ptr);
    	node->mark = 0;
	}
    return;
}

void* gc_calloc(size_t nmemb, size_t size){
    void* ptr = calloc(nmemb, size);
    if(ptr != NULL)
        Node_insert(_metaData, ptr, size);
    return ptr;
}
