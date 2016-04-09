/*
 * dataStructure.c
 *
 * implementation of the data structure
 */

#include "dataStructure.h"


DataStructure* DataStructure_init()
{
    DataStructure* ds = (DataStructure*) malloc(sizeof(DataStructure));
    ds->head = NULL;
    ds->tail = NULL;
    ds->linkSize = 0;
    return ds;
}

void DataStructure_destroy(DataStructure* ds)
{
    if(ds == NULL)
        return;
    Node* current = ds->head;
    Node* temp;
    while(current != NULL)
    {
        temp = current->next;
        current->next = NULL;
        free(current->address);
        free(current);
        current = temp;
    }
    ds->head = NULL;
    ds->tail = NULL;
    ds->linkSize = 0;
    free(ds);
    ds = NULL;
}

void Node_insert(DataStructure* ds, void* address, size_t sizeAllocated)
{
    if(ds == NULL)
    {
        fprintf(stderr, "DataStructure is not initialized\n");
        return;
    }

    Node* newNode = (Node*) malloc(sizeof(Node));
    newNode->mark = 0;
    newNode->size = sizeAllocated;
    newNode->address = address;

    /* When there is no node in the DataStructure, 
        insert the node and set head and tail. */
    if(ds->linkSize == 0)
    {
        ds->head = newNode;
        ds->tail = newNode;
        newNode->next = NULL;
        ds->linkSize++;
        return;
    }

    /* When there are nodes in the DataStructure,
        insert the node based on the size of address. */
    /* Insert from head*/
    if(newNode->address < ds->head->address)
    {
        newNode->next = ds->head;
        ds->head = newNode;
        ds->linkSize++;
    }

    /* Insert from tail */
    else if(newNode->address > ds->tail->address)
    {
        newNode->next = NULL;
        ds->tail->next = newNode;
        ds->tail = newNode;
        ds->linkSize++;
    }

    /* Insert between head and tail */
    else
    {
        Node* current = ds->head;
        Node* previous;
        while(current != NULL && (current->address < newNode->address))
        {
            previous = current;
            current = current->next;
        }

        //current must not equal to NULL
        if(current == NULL)
        {
             fprintf(stderr, "Something Went Wrong. Line: %d\n", __LINE__);
             exit(EXIT_FAILURE);
        }   

        previous->next = newNode;
        newNode->next = current;
        ds->linkSize++;
    }
    return;
}

void Node_remove(DataStructure* ds, void* address)
{
    if(ds == NULL || ds->linkSize == 0)
    {
        fprintf(stderr, "The dataStructure is empty\n");
        return;
    }
    //Only one node in the structure
    if(ds->linkSize == 1)
    {
        free(ds->head->address);
        free(ds->head);
        ds->head = NULL;
        ds->tail = NULL;
        ds->linkSize--;
        return;
    }

    //More than one node in the structure
    //Remove the head
    if(ds->head->address == address)
    {
        Node* temp = ds->head->next;
        free(ds->head->address);
        free(ds->head);
        ds->head = temp;
        ds->linkSize--;
    }
    //Remove the tail
    else if(ds->tail->address == address)
    {
        Node* current = ds->head;
        while(current->next != ds->tail )
            current = current->next;
        current->next = NULL;
        free(ds->tail->address);
        free(ds->tail);
        ds->tail = current;
        ds->linkSize--;
    }
    //Remove from middle
    else
    {
        Node* current = ds->head;
        Node* previous;
        while(current != NULL && current->address != address)
        {
            previous = current;
            current = current->next;
        }   
        if(current == NULL)
        {
            fprintf(stderr, "No Node Matched To Be Removed. Line: %d\n", __LINE__);
            return;
        }
        previous->next = current->next;
        free(current->address);
        free(current);
        current = NULL;
        ds->linkSize--;
    }
    return;
}

void* DataStructure_findNode(DataStructure* ds, void* address)
{
    if(ds == NULL || ds->linkSize == 0)
    {
        fprintf(stderr, "The dataStructure is empty\n");
        return NULL;
    }
    Node* current = ds->head;
    while(current != NULL && current->address != address)
    {
        current = current->next;
    }
    if(current == NULL)
    {
        fprintf(stderr, "No Match Found. Line: %d.\n", __LINE__);
        return NULL;
    }
    return (void*)current->address;
}

void DataStructure_display(DataStructure* ds)
{
    if(ds == NULL || ds->linkSize == 0)
    {
        fprintf(stderr, "The dataStructure is empty\n");
        return;
    }
    Node* current = ds->head;
    int count = 0;
    fprintf(stderr, "Print Each Node:");
    while(current != NULL)
    {
        if(count % 5 == 0)
            fprintf(stderr, "\n");
        fprintf(stderr, "%p ", current->address);
        current = current->next;
        count++;
    }
    fprintf(stderr, "\n");
    fprintf(stderr, "End of Print. \n");
}
































/*
void DataStructure_init(DataStructure* ds){
    size_t size = 10;
    ds->NodeList = malloc(sizeof(Node*) * size);
    ds->NodeListSize = size;
    ds->NodeListCount = 0;
}

void DataStructure_destroy(DataStructure* ds){
}

void Node_insert(DataStructure* ds, void* address){
    
    if(_metaData == NULL){
        _metaData = malloc(sizeof(DataStructure));
        DataStructure_init(_metaData);
    }

    if(ds->NodeListCount == ds->NodeListSize){
        size_t allocationSize = 2 * ds->NodeListSize;
        ds->NodeList = realloc(ds->NodeList, sizeof(Node*) * allocationSize);
        ds->NodeListSize = allocationSize;
    }

    ds->NodeList[ds->NodeListCount] = malloc(sizeof(Node));
    ds->NodeList[ds->NodeListCount]->mark = 0;
    ds->NodeList[ds->NodeListCount]->address = address;
    ds->NodeListCount++;

}

void Node_remove(DataStructure* ds, void* address)
{
    size_t i;
    for(i = 0; i < _metaData->NodeList)
}
*/



