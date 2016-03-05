#include <stdlib.h>
#include "dataStructure.h"

void* gc_calloc(size_t num, size_t size)
{
	void* ptr = calloc(num, size);
	if(ptr != NULL)
		Node_insert(ds, ptr, size);
	return ptr;
}