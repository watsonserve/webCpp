#! /bin/makefile

INC=../../include
framework=../framework
LIB=../../lib

a.out : main.cpp $(framework)/Object.cpp
	g++ $^ -o $@ -I $(INC) -L $(LIB) -lIo -lThread -lLang -lpthread -lrt

