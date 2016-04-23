#ifndef _DATASTRUCTURE_H_
#define _DATASTRUCTURE_H_

typedef struct llNode {
    void* value;
    struct llNode* next;
} llNode;

void ll_insertNode(llNode* head, void* value){
    llNode* n = (llNode*)malloc(sizeof(llNode));
    n->value = value;

    // list is empty
    if(head == NULL){
        head = n;
        n->next = NULL;
        return;
    }
    long stackAddress = (long)value;
    
    // our node is the smallest
    if(stackAddress < *(long*)(head->value)){
        n->next = head;
        head = n;
        return;
    }

    llNode* temp = head;

    while(temp->next && *(long*)(temp->next->value) < value){
        temp = temp->next;
    }

    n->next = temp->next;
    temp->next = n;
}


void* ll_returnMin(llNode* head){
    return head->value;
}

void ll_destroy(){
    llNode* temp = head;

    while(temp){
        free(temp->value);
        free(temp);
    }
}

#endif
