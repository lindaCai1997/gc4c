#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include "dataStructure.h"
#include "malloc.h"

size_t  heap_top;
size_t  heap_bottom;
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

int mark(size_t sp, DataStructure* heapdata){
    int i = 0;
    Node* current = heapdata -> head;
    Node* tail = heapdata -> tail;
    if (current == NULL)
         return 0;
   
    do{ 
        if ((void*)sp ==  current -> address){
            current -> mark = 1;  
            return 1;
        }   
        current = current -> next;
    }while(current != tail);
    return 0;
}

void mark_on_stack(DataStructure *heapdata){
 //   find_stack_bottom();
    size_t i;
    stack_top = (size_t)(&i);
    heap_top = (size_t)heapdata -> head -> address;
    heap_bottom = (size_t)heapdata -> tail -> address;
 //   printf("%zu", stack_top);   
    size_t address_stack = stack_top;
    size_t address_heap = 0;
    for (; address_stack < stack_bottom; address_stack ++){
        address_heap = *(size_t*)address_stack;
        if (address_heap >= heap_top && address_heap <= heap_bottom)
             mark(address_heap, heapdata);
    }

}

void mark_on_heap(DataStructure *heapdata){
    Node* current = heapdata -> head;
    Node* tail = heapdata -> tail;
    heap_top = (size_t)current -> address;
    heap_bottom = (size_t)tail -> address;
    do {
    void* heap_address = current -> address;
    size_t potential_address = 0;
        while (heap_address < current -> address + current -> size){
                potential_address = *(size_t*)heap_address;
                if (potential_address >= heap_top && potential_address <= heap_bottom)
                        mark(potential_address, heapdata);
                heap_address++;
        }
    } while(current != tail);
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
