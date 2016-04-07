#include "../gc4c.h"
#include <stdio.h>
#include <stdlib.h>

int main(){

    printf("test1\n");

    gc_init();
    int*x = malloc(sizeof(int));
    gc_destroy();

}
