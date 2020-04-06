CXX = gcc
OBJ = ../../dist/objs
LIB = ../../dist/lib
INC = ../../include
CXXFLAGS = -c -O3 -Wall --std=c++17 -g

a.out: main.o MsgServer.o $(LIB)/libFramework.a
	g++ -o $@ $^ -lc -lpthread -lstdc++

main.o: main.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@ -I $(INC)

MsgServer.o: MsgServer.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@ -I $(INC)
