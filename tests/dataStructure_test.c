#include <stdio.h>
#include "../inc/DataStructure.h"

void test1(){


    int* x = malloc(sizeof(int));
    *x = 5;
    Node_insert(ds, x);

    printf("%d\n", *(int*)(ds->NodeList[0]->address));


}

int main(){

    test1();

}
