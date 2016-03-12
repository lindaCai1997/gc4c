/*
 * dataStructure.h
 *
 * dataStructure header files
 */

#ifndef _DATASTRUCTURE_H_
#define _DATASTRUCTURE_H_

#include <stdlib.h>
#include <stdio.h>

typedef struct Node{
    int mark;
    size_t size;
    void* address;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
    Node* tail;
    size_t linkSize;
} DataStructure;

static DataStructure* _metaData = NULL;

DataStructure* DataStructure_init();
void DataStructure_destroy(DataStructure*);
void Node_insert(DataStructure*, void*, size_t);
void Node_remove(DataStructure*, void*);
void* DataStructure_findNode(DataStructure*, void*);
void DataStructure_display(DataStructure*);

#endif

/*
typedef struct {
    int mark;
    void* address;
} Node;

typedef struct {
    Node** NodeList;
    size_t NodeListSize;
    size_t NodeListCount;
} DataStructure;

static DataStructure* _metaData = NULL;

void DataStructure_init(DataStructure*);
void DataStructure_destroy(DataStructure*);
void Node_insert(DataStructure*, void*); //we need to add size as a parameter
void Node_remove(DataStructure*, void*);


void dataStructure_findNode(DataStructure*, void*);
*/
