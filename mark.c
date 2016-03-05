#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void* heap_bottom;
void* heap_top; 
extern end;
int mark(void* sp){
        heap_bottom = end;
        heap_top = sbrk(0);
        if (sp >= heap_bottom && sp <= heap_top)
            return 1; 
        return 0;
}
