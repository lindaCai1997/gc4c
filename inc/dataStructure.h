/*
 * dataStructure.h
 *
 * dataStructure header files
 */

#include <stdlib.h>

typedef struct {
    int mark;
    size_t size;
    void* address;
    Node* next;
} Node;

typedef struct {
    Node* head;
    Node* tail;
    size_t linkSize;
} DataStructure;

static DataStructure* _metaData = NULL;

void DataStructure_init(DataStructure*);
void DataStructure_destroy(DataStructure*);
void Node_insert(DataStructure*, void*, size_t); //we need to add size as a parameter
void Node_remove(DataStructure*, void*);
void* DataStructure_findNode(DataStructure*, void*);




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
