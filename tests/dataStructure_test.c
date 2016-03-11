#include <stdio.h>
#include "../inc/DataStructure.h"



void test_insert()
{
    DataStructure* ds = (DataStructure*) malloc(sizeof(DataStructure));
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
}

void test_remove(){
    DataStructure* ds = (DataStructure*) malloc(sizeof(DataStructure));
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
}

void* test_findNode(){
    DataStructure* ds = (DataStructure*) malloc(sizeof(DataStructure));
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
    temp = DataStructure_findNode(ds, &test);
    fprintf(stderr, "Check our DataStructure is not altered\n");
    DataStructure_display(ds);
    DataStructure_destroy(ds);
}

void test_findNode
int main(){
    test_insert();
    test_remove();
    test_findNode();
    return 0;
}







/*
void test1(){


    int* x = malloc(sizeof(int));
    *x = 5;
    Node_insert(ds, x);

    printf("%d\n", *(int*)(ds->NodeList[0]->address));


}

int main(){

    test1();

}
*/