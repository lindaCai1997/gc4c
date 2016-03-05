/*
 * malloc.c
 *
 * malloc.h implementation
 */

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "malloc.h"
#include "dataStructure.h"

#undef malloc
#undef calloc
#undef realloc
#undef free

void* gc_malloc(size_t size){
    void* userData = malloc(size);
    Node_insert(_metaData, userData);
    return userData;
}

void* gc_realloc(void* ptr, size_t size){
    if(ptr == NULL)
        return NULL;
    if(size == 0)
    {
        gc_free(ptr);
        return NULL;
    }
    Node* node = dataStructure_findNode(ds, ptr);
    size_t oldsize = node->size;
    size_t newsize = oldsize > size ? size : oldsize; 

    Node_remove(ds, ptr);

    void* newptr = realloc(ptr, size);
    if(newptr == NULL)
        return NULL;

    Node_insert(ds, newptr, newsize);

    return newptr;
}

void* gc_free(void* ptr){
    return NULL;
}

void* gc_calloc(size_t nmemb, size_t size){
    void* ptr = calloc(num, size);
    if(ptr != NULL)
        Node_insert(ds, ptr, size);
    return ptr;
}
