CC = gcc
CCFLAGS = -std=c99 -c -MMD -MP -D_GNU_SOURCE -Wall
DEBUGFLAGS = -g

all: dataStructure-test.o

debug: dataStructure-test-debug.o

dataStructure-test.o: malloc.o dataStructure.o tests/dataStructure_test.c
	$(CC) malloc.o dataStructure.o tests/dataStructure_test.c -o dataStructure_test

dataStructure-test-debug.o: dataStructure.o tests/dataStructure_test.c
	$(CC) dataStructure.o tests/dataStructure_test.c -o dataStructure_test-debug

malloc.o: dataStructure.o inc/malloc.h inc/malloc.c
	$(CC) $(CCFLAGS) dataStructure.o inc/malloc.h inc/malloc.c 

dataStructure.o: inc/dataStructure.h inc/dataStructure.c
	$(CC) $(CCFLAGS) inc/dataStructure.h inc/dataStructure.c

clean:
	rm -rf *o dataStructure
