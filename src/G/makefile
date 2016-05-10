#bin/bash

ROOT = ../..
OBJ = $(ROOT)/tmp/.objs
INC = $(ROOT)/include
LIB = $(ROOT)/lib/G
SRC = $(ROOT)/src/G

CC = gcc
CXX = g++
AR = ar

CFLAGS = -O3 -c -fPIC -I $(INC)
AFLAGS = crsv

#$(LIB)/G.so : $(LIB)/G.a
	#$(CC) -fPIC -shared -o $@ $^

$(LIB)/G.a : $(LIB)/libGutil.a $(LIB)/libGnet.a $(LIB)/libGmmp.a $(LIB)/libGaio.a
	$(AR) $(AFLAGS) $@ $^

#aio
$(LIB)/libGaio.a : $(OBJ)/gaio.o
	$(AR) $(AFLAGS) $@ $^

$(OBJ)/gaio.o : $(SRC)/gaio.c
	$(CC) $(CFLAGS) $^ -o $@

#memory pool
$(LIB)/libGmmp.a : $(OBJ)/mmp.o
	$(AR) $(AFLAGS) $@ $^

$(OBJ)/mmp.o : mmp.c
	$(CC) $(CFLAGS) $^ -o $@

#net
$(LIB)/libGnet.a : $(OBJ)/Gnet.o
	$(AR) $(AFLAGS) $@ $^

$(OBJ)/Gnet.o : $(SRC)/net/Gnet.c
	$(CC) $(CFLAGS) -o $@ $^

#util
$(LIB)/libGutil.a : $(OBJ)/lnkQS.o $(OBJ)/sort.o $(OBJ)/util.o
	$(AR) $(AFLAGS) $@ $^

$(OBJ)/util.o : util.cpp
	$(CC) $(CFLAGS) -o $@ $^

$(OBJ)/lnkQS.o : lnkQS.c
	$(CC) $(CFLAGS) -o $@ $^

$(OBJ)/sort.o : sort.c
	$(CC) $(CFLAGS) -o $@ $^
