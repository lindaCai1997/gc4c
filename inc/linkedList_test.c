#include <stdio.h>
#include "linkedList.h"

//ll_insertNode
//ll_destroy
//ll_removeNode
int main()
{
	llNode* head = NULL;
	int i;
	for(i = 0; i < 20; i++)
	{
		ll_insertNode(&head, i, i + 1, i + 2);
	}
	llNode* current = head;
	fprintf(stderr, "current: %p\n", current);
	while(current)
	{
		fprintf(stderr, "threadID: %ld, stack_top: %ld, stack_bottom: %ld.\n", current->threadID, current->stack_top, current->stack_bottom);
		current = current->next;
	}
	fprintf(stderr, "remove nodes with theadID = 0 and 5. \n");
	ll_removeNode(&head, 0);
	ll_removeNode(&head, 5);
	current = head;
	while(current)
	{
		fprintf(stderr, "threadID: %ld, stack_top: %ld, stack_bottom: %ld.\n", current->threadID, current->stack_top, current->stack_bottom);
		current = current->next;
	}	
	fprintf(stderr, "destroy the structure.\n");
	ll_destroy(&head);
	return 0;
}