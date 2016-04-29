#include <stdio.h>
#include "../inc/DataStructure.h"



void test_insert()
{
    DataStructure* ds;
    ds = DataStructure_init();
    fprintf(stderr, "Add 10 nodes to our DataStructure\n");
    int* int_arr = (int*) malloc(sizeof(int)*10);
    int i;
    for(i = 0; i < 10; i++)
    {
        int_arr[i] = i;
        Node_insert(ds, &int_arr[i], sizeof(int));
    }
    DataStructure_display(ds);
    DataStructure_destroy(ds);
    free(int_arr);
}

void test_remove(){
    DataStructure* ds;
    ds = DataStructure_init();
    fprintf(stderr, "Add 10 nodes to our DataStructure\n");
    int* int_arr = (int*) malloc(sizeof(int)*10);
    int i;
    for(i = 0; i < 10; i++)
    {
        int_arr[i] = i;
        Node_insert(ds, &int_arr[i], sizeof(int));
    }
    DataStructure_display(ds);
    fprintf(stderr, "Remove even number of nodes\n");
    for(i = 0; i < 10; i = i + 2)
    {
        Node_remove(ds, &int_arr[i]);
    }
    DataStructure_display(ds);
    DataStructure_destroy(ds);
    free(int_arr);
}

void test_findNode(){
    DataStructure* ds;
    ds = DataStructure_init();
    fprintf(stderr, "Add 10 nodes to our DataStructure\n");
    int* int_arr = (int*) malloc(sizeof(int)*10);
    int i;
    for(i = 0; i < 10; i++)
    {
        int_arr[i] = i;
        Node_insert(ds, &int_arr[i], sizeof(int));
    }
    DataStructure_display(ds);
    fprintf(stderr, "Find 3rd and 5th Node\n");
    void* temp;
    temp = DataStructure_findNode(ds, &int_arr[2]);
    fprintf(stderr, "True address: %p; address found: %p\n", &int_arr[2], temp);
    //assert(temp == (void*)&int_arr[2]);
    temp = DataStructure_findNode(ds, &int_arr[4]);
    fprintf(stderr, "True address: %p; address found: %p\n", &int_arr[4], temp);
    //assert(temp == (void*)&int_arr[4]);
    int test = 1;
    //Should not be found!
    fprintf(stderr, "Finding Non-existing Value\n");
    temp = DataStructure_findNode(ds, &test);
    fprintf(stderr, "Check whether our DataStructure is altered\n");
    DataStructure_display(ds);
    DataStructure_destroy(ds);
    free(int_arr);
}

int main(){

    fprintf(stderr, "Testing insert\n");
    test_insert();
    fprintf(stderr, "\n");

    fprintf(stderr, "Testing remove\n");
    test_remove();
    fprintf(stderr, "\n");

    fprintf(stderr, "Testing findNode\n");
    test_findNode();
    fprintf(stderr, "\n");
    return 0;
}