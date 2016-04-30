#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include "mark_and_sweep.h"

size_t  heap_top;
size_t  heap_bottom;
size_t  stack_bottom;
size_t  stack_top;

void set_stack_bottom(size_t bottom){
    stack_bottom = bottom;
	find_stack_bottom();
}

void find_stack_bottom(){
    // the 28th number in /proc/self/stat is the start of the stack
    FILE* statfp = fopen("/proc/self/stat", "r");

    assert(statfp != NULL);
    fscanf(statfp, "%*d %*s %*c %*d %*d %*d %*d %*d %*u %*lu %*lu %*lu %*lu "
			"%*lu %*lu %*ld %*ld %*ld %*ld %*ld %*ld %*llu %*lu %*ld %*lu %*lu %*lu" "%lu", &stack_bottom);
 	fclose(statfp);
//	printf("stack bottom: %zx\n", stack_bottom);	
}


int mark(size_t sp, DataStructure* heapdata){
	Node* current = heapdata -> head;
    
	if (current == NULL)
         return 0;
    do{ 
		if (sp ==  (size_t)(current -> address)){
//            printf("found: %zx\n", (size_t)(current -> address));
			current -> mark = 1; 
            return 1;
		}	
		current = current -> next;
    } while(current != NULL);
    
	return 0;
}

int mark_heap(size_t sp, DataStructure* heapdata){
	Node* current = heapdata -> head;
    heap_top = (size_t)(current -> address);
    heap_bottom = (size_t)(heapdata -> tail -> address);
    
	if (current == NULL)
        return 0;
    do{ 
		if (sp ==  (size_t)(current -> address)){
			if (current -> mark == 1)
				return 1;
            current -> mark = 1; 
			void* heap_address = current -> address;
			size_t potential_address = 0;
			while (heap_address < current -> address + current -> size){
        			potential_address = *(size_t*)heap_address;
        		if (potential_address >= heap_top && potential_address <= heap_bottom)
           			mark_heap(potential_address, heapdata);
        		heap_address += sizeof(size_t);
			}
            return 1;
		}	
		current = current -> next;
    } while(current != NULL);
    
	return 0;

}


void mark_on_stack(DataStructure *heapdata){

	mark_all_on_stack(heapdata);
	find_stack_bottom();
    size_t i = 0;
    stack_top = (size_t)(&i);
	if (heapdata -> head == NULL)
		return;
//	printf("stack_top: %zx\n", stack_top);
	heap_top = (size_t)(heapdata -> head -> address);
    heap_bottom = (size_t)(heapdata -> tail -> address);
   
  	size_t address_stack = stack_top;
    size_t address_heap = 0;
    for (; address_stack < stack_bottom; address_stack += sizeof(size_t)){
		 address_heap = *((size_t*)address_stack);
//		 printf("addess_stack : %zx address_heap:%zx\n", (size_t)address_stack, address_heap);
         if (address_heap >= heap_top && address_heap <= heap_bottom)
             mark(address_heap, heapdata);
    }

}

void mark_on_heap(DataStructure *heapdata){
 
 	Node* current = heapdata -> head;
    Node* tail = heapdata -> tail;

	if (current == NULL || current == tail)
		return;

    heap_top = (size_t)(current -> address);
    heap_bottom = (size_t)(tail -> address);
    do {
		if (current -> mark == 1){
   			void* heap_address = current -> address;
    		size_t potential_address = 0;
    		while (heap_address <= current -> address + current -> size){
        		potential_address = *(size_t*)heap_address;
//		 printf("addess_heap1 : %zx address_heap2:%zx\n", (size_t)heap_address, potential_address);
        		if (potential_address >= heap_top && potential_address <= heap_bottom)
           			mark_heap(potential_address, heapdata);
        		heap_address += sizeof(size_t);
			}
    	}
		current = current -> next;
    } while(current && tail && current != tail);
}

void mark_all_on_stack(DataStructure *heapdata){
	Node* curr = heapdata -> head;
	while (curr != NULL){
		curr -> mark = 0;
	   	curr = curr -> next;		
	}	
}

void mark_all_on_stack_r(DataStructure *heapdata){
    pthread_mutex_lock(&_mark_sweep_mtx);
	Node* curr = heapdata -> head;
	while (curr != NULL){
		curr -> mark = 0;
	   	curr = curr -> next;		
	}	
    pthread_mutex_unlock(&_mark_sweep_mtx);
}

void sweep(DataStructure *heapdata){
	Node* current = heapdata -> head;
	Node* temp = current;
	while (current != NULL){
		if (current -> mark == 0){
//			printf("sizeof dataStructure: %d\n", heapdata -> linkSize);
//			printf("remove at address: %zx\n", current -> address); 
			temp = current;
			current = current -> next;
			Node_remove(heapdata, temp -> address);
		}
		else {
			current = current -> next;
		}
	}
}
