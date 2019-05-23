cc = gcc
CFLAGS = -std=c11 -Wall
INCLUDES = -I./include

.PHONY:clean

libtest.a: test.o
	ar crv libtest.a test.o

test.o :src/test.c include/test.h
	$(cc) -c $(CFLAGS) $(INCLUDES) src/test.c

install : 
	cp include/* output/include
	cp libtest.a output/libs 

clean : 
	rm -rf *.o  *.a
