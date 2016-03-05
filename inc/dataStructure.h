/*
 * dataStructure.h
 *
 * dataStructure header files
 */

#include <stdlib.h>

typedef struct {
    int mark;
    void* address;
} Node;

typedef struct {
    Node** NodeList;
    size_t NodeListSize;
    size_t NodeListCount;
} DataStructure;

DataStructure* _metaData = NULL;

void DataStructure_init(DataStructure*);
void DataStructure_destroy(DataStructure*);
void Node_insert(DataStructure*, void*);
void Node_remove(DataStructure*, void*);
