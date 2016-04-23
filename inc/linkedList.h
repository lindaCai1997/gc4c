#ifndef _DATASTRUCTURE_H_
#define _DATASTRUCTURE_H_

typedef struct llNode {
    void* value;
    struct llNode* next;
} llNode;


void ll_insertNode(llNode* head, void* value);
void* ll_returnMin(llNode* head);
void ll_destroy();
void ll_removeNode(llNode* head, void* value);


#endif
