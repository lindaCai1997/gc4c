CC = clang
CCFLAGS = -std=c99 -c -MMD -MP -D_GNU_SOURCE -Wall
DEBUGFLAGS = -g
ASANFLAGS = -fsanitize=leak -fno-omit-frame-pointer

all: test1 test2 
debug: test-debug test2-debug
asan: test1-asan test2-asan test1-without-gc4c-asan

test1: malloc dataStructure mark_and_sweep tests/test1.c
	$(CC) malloc.o dataStructure.o mark_and_sweep.o tests/test1.c -o test1.exe

test1-debug: malloc dataStructure mark_and_sweep tests/test1.c
	$(CC) $(DEBUGFLAGS) malloc.o dataStructure.o mark_and_sweep.o tests/test1.c -o test1-debug.exe

test1-asan: malloc dataStructure mark_and_sweep tests/test1.c
	$(CC) $(ASANFLAGS) malloc.o dataStructure.o mark_and_sweep.o tests/test1.c -o test1-asan.exe

test1-without-gc4c-asan: tests/test1-without-gc4c.c
	$(CC) $(ASANFLAGS) tests/test1-without-gc4c.c -o test1-without-gc4c-asan.exe

test2: malloc dataStructure mark_and_sweep tests/test2.c
	$(CC) malloc.o dataStructure.o mark_and_sweep.o tests/test2.c -o test2.exe

test2-debug: malloc dataStructure mark_and_sweep tests/test2.c
	$(CC) $(DEBUGFLAGS) malloc.o dataStructure.o mark_and_sweep.o tests/test2.c -o test2-debug.exe

test2-asan: malloc dataStructure mark_and_sweep tests/test2.c
	$(CC) $(ASANFLAGS) malloc.o dataStructure.o mark_and_sweep.o tests/test2.c -o test2-asan.exe

malloc: dataStructure inc/malloc.h inc/malloc.c
	$(CC) $(CCFLAGS) dataStructure.o inc/malloc.h inc/malloc.c -c

dataStructure: inc/dataStructure.h inc/dataStructure.c
	$(CC) $(CCFLAGS) inc/dataStructure.h inc/dataStructure.c -c

mark_and_sweep: inc/mark_and_sweep.h inc/mark_and_sweep.c 
	$(CC) $(CCFLAGS) inc/mark_and_sweep.h inc/mark_and_sweep.c -c 

clean:
	rm -rf *o *.exe
