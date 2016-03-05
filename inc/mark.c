#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include "dataStructure.h"

size_t   heap_top;
size_t  stack_bottom;
size_t  stack_top;

void find_stack_bottom(){
    // the 28th number in /proc/self/stat is the start of the stack
    FILE* statfp = fopen("/proc/self/stat", "r");
    assert(statfp != NULL);
    fscanf(statfp, "%*d %*s %*c %*d %*d %*d %*d %*d %*u "
           "%*lu %*lu %*lu %*lu %*lu %*lu %*ld %*ld "
           "%*ld %*ld %*ld %*ld %*llu %*lu %*ld "
           "%*lu %*lu %*lu %lu", &stack_bottom);
    fclose(statfp);
}


void mark_on_stack(DataStructure *heapdata){
    find_stack_bottom();
    size_t i;
    stack_top = (size_t)(&i);
    printf("%zu", stack_top);
    size_t address = stack_top;
    for (; address < stack_bottom; address ++){
        mark(address, heapdata);
    }

}

int mark(size_t sp, DataStructure* heapdata){
    int i = 0;
    for (i = 0; i < heapdata -> NodeListSize; i++){
        if ((void*)sp == heapdata -> NodeList[i] -> address)
            heapdata -> NodeList[i] -> mark = 1;
            return 1;
    }
    return 0;
}
int main(){

    DataStructure* heapdata = malloc(sizeof(DataStructure));
    DataStructure_init(heapdata);

    find_stack_bottom();
    mark_on_stack(heapdata);

    printf("%d", heapdata -> NodeListSize);

    free(heapdata);
    heapdata = NULL;
    return 0;
}
