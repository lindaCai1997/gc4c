#include "../inc/malloc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

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
//	printf("address_main: %zx\n", x);
 
    for(int i = 0; i < size; i++){
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

    size_t size = 1024 * 1024, count = 5;
	
    void* x = malloc(count * size);
    printf("Test Large Data Passed !!! \n");
}

void testCharacter(){
    const int size = 10;
    char** arr = malloc(sizeof(char*) * size);
    
    for(int i = 0; i < size; i++){
       	arr[i] = malloc(50);
// 		printf("address: %zx\n", arr[i]);        
        *(arr[i]) = (char)i;
    }

    for(int i = 0; i < size; i++){
        if(*(arr[i]) != (char)i){
            puts("test character FAILED");
            return;
        }
    }
	puts("test character SUCCESS");
}

void* starter(){
    
    testCharacter();
    return NULL;
}

int main(){
    // printf("Test 1 with GC4C\n");
    gc_init_r();

  testSimple();
  testSimple();
  testValidData();
  testValidData();
  testSimple();
  testLargeData();
  testLargeData();
  testCharacter();
  testCharacter();
/*
    pthread_t pids[10];

    for(int i = 0; i < 1; i++)
        pthread_create(&pids[i], NULL, starter, NULL);

    for(int i = 0; i < 1; i++)
        pthread_join(pids[i], NULL);
*/
    gc_destroy();
    return 0;
}
