#include "linkedList.h"
#include <stdlib.h>
#include <stdio.h>

void ll_insertNode(llNode** head, long threadID, long stack_top, long stack_bottom){
    llNode* n = (llNode*)malloc(sizeof(llNode));

    n->threadID = threadID;
    n->stack_top = stack_top;
    n->stack_bottom = stack_bottom;

    // list is empty
    if(*head == NULL){
        *head = n;
        n->next = NULL;
        // fprintf(stderr, "head: %p\n", *head );
        return;
    } else {
        n->next = *head;
        *head = n;
        return;
    }
}


void ll_destroy(llNode** head){
    llNode* current = *head;
    llNode* temp = NULL;
    while(current != NULL){
        temp = current->next;
        current->next = NULL;
        free(current);
        current = temp;
    }

}

void ll_removeNode(llNode** head, long threadID){
    llNode *temp = *head, *prev = NULL;

    while(temp){
        if(temp->threadID == threadID){
            if(prev)
                prev->next = temp->next;
            if(temp == *head)
                *head = temp->next;
            temp->next = NULL;
            free(temp);
            break;
        }   
        if(prev == NULL)
            prev = *head;
        else
            prev = prev->next;
        temp = temp->next;
    }
}
