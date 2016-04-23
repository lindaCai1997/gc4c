#include "linkedList.h"

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
        free(temp);
        temp = temp->next;
    }
}

void ll_removeNode(llNode* head, void* value){
    long v = *(long*)value;

    llNode *temp = head, *prev = NULL;

    while(temp){
        if(*(long*)(temp->value) == v){
            if(prev)
                prev->next = temp->next;
            if(temp == head)
                head = temp->next;
            temp->next = NULL;
            free(temp);
        }   
        if(prev == NULL)
            prev = head;
        else
            prev = prev->next;
        temp = temp->next;
    }
}
