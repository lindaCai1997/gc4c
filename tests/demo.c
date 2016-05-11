#include "../inc/malloc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

void testShowcase(){
    printf("---- Test Showcase ----\n");
	size_t size = 7;
	time_t t;
	srand((unsigned) time(&t));
    void** x = (void**) malloc(sizeof(void*)*size);
	//pre-allocate some memory
    for(size_t i = 0; i < size; i++){
        x[i] = (void*) malloc(rand()%200);
		sleep(1);
	}
	size_t animation_count = 20;
	size_t current_node_num = size;
	while(animation_count != 0)
	{
		double random_num =  ((double)rand()/RAND_MAX) >= 0.5;

		size_t remove =	random_num;
		if(current_node_num < 3)
			remove = 0;
		if(current_node_num > 5)
			remove = 1;
		if(remove == 1)
		{
		//	fprintf(stderr, "node are being removed.\n");
			size_t	repeat = 1;
			if(random_num >= 0.75)
				repeat = 2; 
			while(repeat)
			{
				size_t index_to_be_removed = rand()%size;
				while(x[index_to_be_removed] == &t)
					index_to_be_removed = rand()%size;
				x[index_to_be_removed] = &t;
				current_node_num--;
				repeat--;
				//	sleep(1);
			}
		}
		else
		{
		//	fprintf(stderr,"node are being added.\n");
			size_t repeat = 1;
			if(random_num <= 0.25)
				repeat = 2;
			while(repeat)
			{

				for(size_t j = 0; j < size; j++)
				{
					if(x[j] == &t)
					{
						x[j] = malloc(rand()%200);
						sleep(1);
						current_node_num++;
						break;
					}
				}
				repeat--;
			}
		}		

		animation_count--;
	}
}

int main(){
    gc_init_r();
	testShowcase();
    gc_destroy();
    return 0;
}
