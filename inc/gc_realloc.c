#include <stdlib.h>
#include "dataStructure.h"

void* gc_realloc(void* ptr, size_t size)
{
	if(ptr == NULL)
		return NULL;
	if(size == 0)
	{
		gc_free(ptr);
		return NULL;
	}
	Node* node = dataStructure_findNode(ds, ptr);
	size_t oldsize = node->size;
	size_t newsize = oldsize > size ? size : oldsize; 

	Node_remove(ds, ptr);

	void* newptr = realloc(ptr, size);
	if(newptr == NULL)
		return NULL;

	Node_insert(ds, newptr, newsize);

	return newptr;
}
