#include "../inc/malloc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void testSimple(){
    printf("---- Test Simple ----\n");
    int** x = malloc(10 * sizeof(int*));

    for(int i = 0; i < 10; i++){
        x[i] = malloc(sizeof(int));
    }
    printf("Test Simple PASSED !!!\n");
}

void testValidData(){

    printf("--- Test Valid Data ---\n");

    int size = 100;

    int** x = malloc(size * sizeof(int*));

    for(int i = 0; i < size; i++){
        x[i] = malloc(sizeof(int));
        *(x[i]) = i;
    }

    for(int i = 0; i < size; i++){
        if(*(x[i]) != i){
           printf("test valid data FAILED !!!\n"); 
           return;
        }
    }

    printf("test valid data PASSED !!!\n");

}


void testLargeData(){
    printf("--- Test Large Data ---\n");

    size_t size = 1024 * 1024 * 1024, count = 5;

    void* x = malloc(count * size);
    printf("Test Large Data Passed !!! \n");
}

int main(){
    // printf("Test 1 with GC4C\n");
    gc_init();
    testSimple();
    testValidData();
    testLargeData();
    gc_destroy();
    return 0;
}
