#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <assert.h>
#include "dataStructure.h"

#ifndef _MARK_H_
#define _MARK_H_
void find_stack_bottom();
int mark(size_t sp, DataStructure *heapdata);
void mark_on_stack(DataStructure *heapdata);
void mark_on_heap(DataStructure *heapdata);
void mark_all_on_stack(DataStructure *heapdata);
void sweep(DataStructure *heapdata);

#endif
