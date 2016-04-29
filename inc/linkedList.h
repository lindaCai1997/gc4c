#ifndef _LINKED_LIST_H_
#define _LINKED_LIST_H_

typedef struct llNode {
    long threadID;
    long stack_top;
    long stack_bottom;
    struct llNode* next;
} llNode;


void ll_insertNode(llNode** head, long threadID, long stack_top, long stack_bottom);
void ll_destroy(llNode** head);
void ll_removeNode(llNode** head, long threadID);


#endif
