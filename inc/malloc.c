/*
 * malloc.c
 *
 * malloc.h implementation
 */

#include "malloc.h"

#undef malloc
#undef calloc
#undef realloc
#undef free


void* clean_helper()
{
    mark_on_stack(_metaData);
    mark_on_heap(_metaData);
    sweep(_metaData);
    return NULL;
}

void gc_init()
{
    if(_metaData == NULL)
        _metaData = DataStructure_init();
}

void gc_destroy()
{
    mark_all_on_stack(_metaData);
//    mark_on_heap(_metaData);
    sweep(_metaData);
    DataStructure_destroy(_metaData);
}
void* gc_malloc(size_t size)
{
    if(_metaData == NULL)
        _metaData = DataStructure_init();    
    clean_helper();
    printf("calling gc_malloc\n");
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
    node->mark = 0;
    return;
}

void* gc_calloc(size_t nmemb, size_t size){
    void* ptr = calloc(nmemb, size);
    if(ptr != NULL)
    {
        if(_metaData == NULL)
            _metaData = DataStructure_init();
        Node_insert(_metaData, ptr, size);
    }
    return ptr;
}
