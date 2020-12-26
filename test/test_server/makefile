CXX = gcc
OBJ = ./objs
LIB = ../../dist/lib
INC = ../../include
CXXFLAGS = -c -O3 -Wall --std=c++17 -g

a.out: $(OBJ)/main.o $(OBJ)/MsgServer.o
	g++ -o $@ $^ -L $(LIB) -l Framework -lc -lpthread -lstdc++

$(OBJ)/main.o: main.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@ -I $(INC)

$(OBJ)/MsgServer.o: MsgServer.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@ -I $(INC)
