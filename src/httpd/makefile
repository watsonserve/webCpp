########################################
#
# GHTTPd
# 1.0
# (c) 2016 WatsonSserve
# made by JamesWatson
# All right reserved.
#
# on linux
#
########################################

ROOT = ../..
OBJ = $(ROOT)/tmp/.objs
ASM = $(ROOT)/tmp/.asms
INC = $(ROOT)/include
LIB = $(ROOT)/lib
SRC = $(ROOT)/src/httpd
BIN = $(ROOT)/bin

CXX = g++
CC = gcc
AR = ar
AS = as
LD = ld

CFLAGS = -c -O3 -Wall
ARFLAGS = crsv

$(BIN)/webCpp : $(OBJ)/httpd.o $(OBJ)/Route.o $(OBJ)/HTTPSession.o $(LIB)/G/libGhttpd.a $(LIB)/G/libGserver.a $(LIB)/G/libGio.a $(LIB)/G/libGobject.a $(LIB)/G/libGnet.a $(LIB)/G/libGutil.a
	$(CXX) $(LDFLAGS) $^ -o $@ -ldl -lpthread -lc -lrt

$(OBJ)/httpd.o : $(SRC)/main.cpp
	$(CC) $(CFLAGS) $^ -o $@ -I $(INC)

$(OBJ)/Route.o : $(SRC)/httpd/Route.cpp
	$(CC) $(CFLAGS) $^ -o $@ -I $(INC)

$(OBJ)/HTTPSession.o : $(SRC)/httpd/HTTPSession.cpp
	$(CC) $(CFLAGS) $^ -o $@ -I $(INC)
