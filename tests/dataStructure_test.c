#include <stdio.h>
#include "../inc/DataStructure.h"

void test1(){

    DataStructure* ds = malloc(sizeof(DataStructure));

    DataStructure_init(ds);

    int* x = malloc(sizeof(int));
    *x = 5;
    Node_insert(ds, x);

    printf("%d\n", *(int*)(ds->NodeList[0]->address));

    DataStructure_destroy(ds);

}

int main(){

    test1();

}
