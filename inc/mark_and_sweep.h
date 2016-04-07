#ifndef _MARK_H_
#define _MARK_H_
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include "dataStructure.h"

void find_stack_bottom();
void mark_on_stack(DataStructure*);
int mark(size_t, DataStructure*);

//we should add this function for freeing all memory before main thread returns
void mark_all_on_stack(DataStructure*);

#endif
