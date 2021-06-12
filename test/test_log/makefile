ROOT = ../..
INC = $(ROOT)/include
SRC = $(ROOT)/src/framework

a.out : test_log.o log.o
	gcc -o $@ $^

test_log.o : test_log.c
	gcc -c $^ -o $@ -I $(INC)

log.o : $(SRC)/log.c
	gcc -c $^ -o $@ -I $(INC)
