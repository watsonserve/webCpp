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

ROOT = ..
OBJ = /tmp/.objs
INC = $(ROOT)/include
LIB = $(ROOT)/lib
SRC = $(ROOT)/src
BIN = $(ROOT)/bin

CXX = g++
CC = gcc
AR = ar
AS = as
LD = ld

CFLAGS = -c -O3 -Wall
ARFLAGS = crsv

WEBCPP = $(LIB)/libFramework.so

$(BIN)/webcpp : $(OBJ)/httpd.o $(OBJ)/Route.o $(OBJ)/HTTPSession.o $(LIB)/libNet.a $(LIB)/libIo.a $(LIB)/libLang.a $(LIB)/libThread.a $(LIB)/libException.a
	$(CXX) $(LDFLAGS) $^ -o $@ -ldl -lpthread -lrt -lc -lstdc++ --std=c++11

$(OBJ)/httpd.o : $(SRC)/main.cpp
	$(CC) $(CFLAGS) $^ -o $@ -I $(INC)

$(OBJ)/Route.o : $(SRC)/httpd/Route.cpp
	$(CC) $(CFLAGS) $^ -o $@ -I $(INC)

$(OBJ)/HTTPSession.o : $(SRC)/httpd/HTTPSession.cpp
	$(CC) $(CFLAGS) $^ -o $@ -I $(INC)
