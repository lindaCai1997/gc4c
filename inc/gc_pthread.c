/*
 * gc_pthread.c
 */

#include "gc_pthread.h"
#include <pthread.h>

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
/*
void PrintStackInfo (void){   
    pthread_attr_t Attributes;
    void *StackAddress;
    int StackSize;

    // Get the pthread attributes
    memset (&Attributes, 0, sizeof (Attributes));
    pthread_getattr_np (pthread_self(), &Attributes);

    // From the attributes, get the stack info
    pthread_attr_getstack (&Attributes, &StackAddress, &StackSize);

    // Done with the attributes
    pthread_attr_destroy (&Attributes);

    printf ("Stack top:     %p\n", StackAddress);
    printf ("Stack size:    %u bytes\n", StackSize);
    printf ("Stack bottom:  %p\n", StackAddress + StackSize);
}


int gc_pthread_create(pthread_t *thread, const pthread_attr_t *attr,
                           void *(*start_routine) (void *), void *arg){
    int ret = pthread_create(thread, attr, start_routine, arg);
    gc_pthread_add_thread((long)thread, 0, 0);
    return ret; 
}
*/

int gc_pthread_join(pthread_t thread, void** retval){
    ll_removeNode(&pthread_ll_head, (long)thread);
    return pthread_join(thread, retval);
}

