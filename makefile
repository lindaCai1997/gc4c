CC = gcc
CCFLAGS = -c -Wall
DEBUGFLAGS = -g

all: dataStructure-test.o

debug: dataStructure-test-debug.o

dataStructure-test.o: dataStructure.o tests/dataStructure_test.c
	$(CC) dataStructure.o tests/dataStructure_test.c -o dataStructure_test

dataStructure-test-debug.o: dataStructure.o tests/dataStructure_test.c
	$(CC) dataStructure.o tests/dataStructure_test.c -o dataStructure_test-debug

dataStructure.o: inc/dataStructure.h inc/dataStructure.c
	$(CC) $(CCFLAGS) inc/dataStructure.h inc/dataStructure.c

clean:
	rm -rf *o dataStructure
