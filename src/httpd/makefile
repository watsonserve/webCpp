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
OBJ = /tmp/.objs
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

WEBCPP = $(LIB)/G/libGhttpd.a $(LIB)/G/libGserver.a $(LIB)/G/libGio.a $(LIB)/G/libGobject.a $(LIB)/G/libGnet.a $(LIB)/G/libGutil.a

$(BIN)/test : $(OBJ)/httpd.o $(OBJ)/Route.o $(OBJ)/HTTPSession.o $(WEBCPP)
	$(CXX) $(LDFLAGS) $^ -o $@ -ldl -lpthread -lc -lrt

$(OBJ)/httpd.o : $(SRC)/main.cpp
	$(CC) $(CFLAGS) $^ -o $@ -I $(INC)

$(OBJ)/Route.o : $(SRC)/httpd/Route.cpp
	$(CC) $(CFLAGS) $^ -o $@ -I $(INC)

$(OBJ)/HTTPSession.o : $(SRC)/httpd/HTTPSession.cpp
	$(CC) $(CFLAGS) $^ -o $@ -I $(INC)
