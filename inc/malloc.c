/*
 * malloc.c
 *
 * malloc.h implementation
 */

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "dataStructure.h" 
#include "malloc.h"


#undef malloc
#undef calloc
#undef realloc
#undef free

void gc_init()
{
    _metaData = DataStructure_init();
    //user calls this at the beginning of the program
    //we need to create a gc_thread to clean data
}

void gc_destroy()
{
    DataStructure_destroy(_metaData);
    //user calls this at the end of program
    //we need to stop the gc_thread that we have created in the gc_init()
}

void* gc_malloc(size_t size){
    void* userData = malloc(size);
    Node_insert(_metaData, userData, size);
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
    Node* node = (Node*)DataStructure_findNode(_metaData, ptr);
    node->mark = 1;
    return;
}

void* gc_calloc(size_t nmemb, size_t size){
    void* ptr = calloc(nmemb, size);
    if(ptr != NULL)
        Node_insert(_metaData, ptr, size);
    return ptr;
}
