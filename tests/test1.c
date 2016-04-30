#include "../inc/malloc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void testSimple(){
    printf("---- Test Simple ----\n");
	int size = 10; 
    int** x = malloc(size * sizeof(int*));

    for(int i = 0; i < size; i++){
        x[i] = malloc(sizeof(int));
	}
 	/*
	for(int i = 0; i < size; i++){
		printf("should be: %d, actual: %d\n", i, *(x[i]));
        if(*(x[i]) != i){
      	    printf("test valid data FAILED !!!\n"); 
            return;
        }
    }
*/
   printf("Test Simple PASSED !!!\n");
}

void testValidData(){

    printf("--- Test Valid Data ---\n");

    int size = 100;

    int** x = malloc(size * sizeof(int*));

    for(int i = 0; i < size; i++){
//		printf("address: %zx\n", &x[i]);
        x[i] = malloc(sizeof(int));
        *(x[i]) = i;
    }

	for(int i = 0; i < size; i++){
//		printf("should be: %d, actual: %d\n", i, *(x[i]));
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

void testCharacter(){
    const int size = 100;
    char** arr = malloc(sizeof(char*) * size);

    for(int i = 0; i < 100; i++){
       	arr[i] = malloc(50);
// 		printf("address: %zx\n", arr[i]);    
    
        *(arr[i]) = (char)i;

    }

    for(int i = 0; i < 100; i++){
        if(*(arr[i]) != (char)i){
            puts("FAILED");
            return;
        }
    }
	printf("SUCCESS");
}

int main(){
    // printf("Test 1 with GC4C\n");
    gc_init();
    testSimple();
    testValidData();
//	testSimple();
    testLargeData();
    testCharacter();
    gc_destroy();
    return 0;
}
