/*
 * dataStructure.c
 *
 * implementation of the data structure
 */

#include <stdlib.h>
#include "dataStructure.h"

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
