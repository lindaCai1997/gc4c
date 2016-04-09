#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "../inc/malloc.h"

//test cases for gc 
void test_gc_one_layer(){
    gc_init();
    printf("--test gc--\n");

    int* int_arr[10];
    int answer[10];
    int i = 0;
    //store data into datastructure manually for now
    for (i = 0; i < 10; i++){
        answer[i] = 1;
        int_arr[i]  = (int*) malloc(sizeof(int));
        printf("address stack: %zx, address heap: %zx\n",
                (size_t)&int_arr[i], (size_t)int_arr[i]);

    }

    int_arr[9] = NULL;
    int_arr[5] = NULL;
    answer[9] = 0;
    answer[5] = 0;
    int* new_int = malloc(sizeof(int));
    printf("address stack: %zx, address heap: %zx\n",
            (size_t)&new_int, (size_t)new_int);
    gc_destroy();
}

void test_gc_two_layer(){
    gc_init();
    printf("--test gc2--\n");

    int** int_arr[5];
    int answer[10];
    int i = 0;
    //store data into datastructure manually for now
    for (i = 0; i < 5; i++){
        answer[i] = 1;
        int_arr[i]  = (int**) malloc(sizeof(int*));
        *(int_arr[i]) = (int*) malloc(sizeof(int));
        printf("address stack: %zx, address heap1: %zx, address heap2: %zx\n",
                (size_t)&int_arr[i], (size_t)int_arr[i], (size_t)(*(int_arr[i])));
    }
    int_arr[3] = NULL;
    int_arr[4] = NULL;
    answer[9] = 0;
    answer[5] = 0;
    int* good = malloc(sizeof(int));
    printf("address stack: %zx, address heap: %zx\n", (size_t)&good, (size_t)good);
    gc_destroy();
}

int main(){
    test_gc_two_layer();
    test_gc_one_layer();
    return 0;
}
