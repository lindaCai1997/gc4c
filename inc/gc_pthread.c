/*
 * gc_pthread.c
 */

#include "gc_pthread.h"

#undef pthread_create
#undef pthread_join


/*extern DataStructure* _pthread_ds = NULL;

void gc_pthread_init(){
    _pthread_ds = (DataStructure*)malloc(sizeof(DataStructure));
   DataStructure_init(_pthread_ds); 
}

void gc_pthread_destroy(){
    DataStructure_destroy(_pthread_ds);
}

int gc_pthread_create(pthread_t *thread, const pthread_attr_t *attr,
                           void *(*start_routine) (void *), void *arg){
    if(_pthread_ds == NULL)
        gc_pthread_init();
    int ret = pthread_create(thread, attr, start_routine, arg);
    Node_insert(thread, pid);
    return ret; 
}

int gc_pthread_join(pthread_t thread, void** retval){
    if(_pthread_ds != NULL){
        Node_remove(_pthread_ds, &thread);

        if(_pthread_ds->linkSize == 0){
            gc_pthread_destroy();
            free(_pthread_ds);
            _pthread_ds = NULL;
        }
    }

    return pthread_join(thread, retval);
}*/



int gc_pthread_create(pthread_t *thread, const pthread_attr_t *attr,
                           void *(*start_routine) (void *), void *arg){
    int ret = pthread_create(thread, attr, start_routine, arg);
    ll_insertNode(pthread_ll_head, thread);
    return ret; 
}

int gc_pthread_join(pthread_t thread, void** retval){
    ll_removeNode(pthread_ll_head, &thread);
    return pthread_join(thread, retval);
}
