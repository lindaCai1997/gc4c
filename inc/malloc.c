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
    return NULL;
}

void* gc_free(void* ptr){
    return NULL;
}

void* gc_calloc(size_t nmemb, size_t size){
    return NULL;
}
