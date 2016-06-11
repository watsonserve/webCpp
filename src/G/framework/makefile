########################################
#
# framework
# 1.0
# (c) 2016 WatsonSserve
# made by JamesWatson
# All right reserved.
#
# on linux
#
########################################

ROOT = ../../..
OBJ = $(ROOT)/tmp/.objs
ASM = $(ROOT)/tmp/.asms
INC = $(ROOT)/include
LIB = $(ROOT)/lib
SRC = $(ROOT)/src/G/framework
BIN = $(ROOT)/bin

CXX = g++
CC = gcc
AR = ar
AS = as
LD = ld

CFLAGS = -c -O3 -Wall --std=c++11
ARFLAGS = crsv
#LDFLAGS = -s

#framework
$(LIB)/G/framework.so : $(LIB)/G/libGhttpd.a $(LIB)/G/libGserver.a $(LIB)/G/libGio.a $(LIB)/G/libGobject.a
	$(CC) -fPIC -shared -o $@ $^

#object
$(LIB)/G/libGobject.a : $(OBJ)/G/framework/Object.o
	$(AR) $(ARFLAGS) $@ $^

$(OBJ)/G/framework/Object.o : $(SRC)/Object.cpp
	$(CC) $(CFLAGS) $^ -o $@ -I $(INC)

#io
$(LIB)/G/libGio.a : $(OBJ)/G/framework/StreamIO.o $(OBJ)/G/framework/Output.o $(OBJ)/G/framework/Input.o $(OBJ)/G/framework/Aio.o
	$(AR) $(ARFLAGS) $@ $^

$(OBJ)/G/framework/StreamIO.o : $(SRC)/IO/StreamIO.cpp
	$(CC) $(CFLAGS) $^ -o $@ -I $(INC)

$(OBJ)/G/framework/Output.o : $(SRC)/IO/Output.cpp
	$(CC) $(CFLAGS) $^ -o $@ -I $(INC)

$(OBJ)/G/framework/Input.o : $(SRC)/IO/Input.cpp
	$(CC) $(CFLAGS) $^ -o $@ -I $(INC)

$(OBJ)/G/framework/Aio.o : $(SRC)/IO/Aio.cpp
	$(CC) $(CFLAGS) $^ -o $@ -I $(INC)

#server
$(LIB)/G/libGserver.a : $(OBJ)/G/framework/TCPServer.o $(OBJ)/G/framework/Server.o
	$(AR) $(ARFLAGS) $@ $^

$(OBJ)/G/framework/TCPServer.o : $(SRC)/net/TCPServer.cpp
	$(CC) $(CFLAGS) $^ -o $@ -I $(INC)

$(OBJ)/G/framework/Server.o : $(SRC)/Server.cpp
	$(CC) $(CFLAGS) $^ -o $@ -I $(INC)

#httpd
$(LIB)/G/libGhttpd.a : $(OBJ)/G/framework/HTTPd/Dispatcher.o $(OBJ)/G/framework/HTTPd/Request.o $(OBJ)/G/framework/HTTPd/Response.o $(OBJ)/G/framework/HTTPd/Gram.o
	$(AR) $(ARFLAGS) $@ $^

$(OBJ)/G/framework/HTTPd/Dispatcher.o : $(SRC)/net/httpd/HTTPDispatcher.cpp
	$(CC) $(CFLAGS) $^ -o $@ -I $(INC)

$(OBJ)/G/framework/HTTPd/Request.o : $(SRC)/net/httpd/HTTPRequest.cpp
	$(CC) $(CFLAGS) $^ -o $@ -I $(INC)

$(OBJ)/G/framework/HTTPd/Response.o : $(SRC)/net/httpd/HTTPResponse.cpp
	$(CC) $(CFLAGS) $^ -o $@ -I $(INC)

$(OBJ)/G/framework/HTTPd/Gram.o : $(SRC)/net/httpd/HTTPGram.cpp
	$(CC) $(CFLAGS) $^ -o $@ -I $(INC)
