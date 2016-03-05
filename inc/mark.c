#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include "dataStructure.h"


extern end;
size_t   heap_top;
size_t*  stack_bottom;
size_t*  stack_top;

void find_stack_bottom(){
    // the 28th number in /proc/self/stat is the bottom of the stack
    FILE* statfp = fopen("/proc/self/stat", "r");
    assert(statfp != NULL);
    fscanf(statfp, "%*d %*s %*c %*d %*d %*d %*d %*d %*u "
           "%*lu %*lu %*lu %*lu %*lu %*lu %*ld %*ld "
           "%*ld %*ld %*ld %*ld %*llu %*lu %*ld "
           "%*lu %*lu %*lu %lu", stack_bottom);
    fclose(statfp);
}


void  mark_on_stack(DataStructure *heapdata){
    find_stack_bottom();
    size_t i;
    stack_top = &i;
    size_t* address = stack_top;
    for (; address < stack_bottom; address ++){
        mark(address, heapdata);
    }

}

int mark(size_t* sp, DataStructure* heapdata){

    if (*sp >= end && *sp <= heap_top){
        Node_insert(heapdata, (void*)(*sp));
        return 1;
    }
    return 0;
}

int main(){
    heap_top = (size_t)sbrk(0);
    DataStructure* heapdata = malloc(sizeof(DataStructure));
    DataStructure_init(heapdata);
    stack_bottom = malloc(sizeof(size_t));
    mark_on_stack(heapdata);
    printf("%d", heapdata -> NodeListSize);
    free(heapdata);
    heapdata = NULL;
    free(stack_bottom);
    stack_bottom = NULL;
    return 0;
}
