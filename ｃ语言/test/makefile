cc = gcc
CFLAGS = -DTESTFUNC -std=c11 -Wall
BLOS = main.o add.o is_prime.o test.o
.PHONY:clean

a.out : $(BLOS)
	$(cc) $(CFLAGS) $(BLOS)

main.o : main.c
	$(cc) $(CFLAGS) -c  main.c
add.o : add.c add.h
	$(cc) $(CFLAGS) -c add.c
is_prime.o : is_prime.c is_prime.h
	$(cc) $(CFLAGS) -c  is_prime.c
test.o : test.c test.h
	$(cc) $(CFLAGS) -c test.c

clean : 
	rm -rf *.o a.out
