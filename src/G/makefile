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


$(LIB)/G.so : $(LIB)/libGutil.a $(LIB)/libGnet.a
	$(CXX) -shared -fPIC -o $@ $^

#net
$(LIB)/libGnet.a : $(OBJ)/Gnet.o
	$(AR) $(AFLAGS) $@ $^

$(OBJ)/Gnet.o : $(SRC)/net/Gnet.c
	$(CC) $(CFLAGS) -o $@ $^

#util
$(LIB)/libGutil.a : $(OBJ)/util.o
	$(AR) $(AFLAGS) $@ $^

$(OBJ)/util.o : util.cpp
	$(CC) $(CFLAGS) -o $@ $^
