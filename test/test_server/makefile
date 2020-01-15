CXX = gcc
OBJ = ../../dist/objs
INC = ../../include
CXXFLAGS = -c -O3 -Wall --std=c++17

a.out: main.o MsgServer.o $(OBJ)/framework_Exception_Exception_cpp.o net.a ../../dist/lib/libEvent.a ../../dist/lib/libThread.a
	g++ -o $@ $^ -lpthread

main.o: main.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@ -I $(INC)

MsgServer.o: MsgServer.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@ -I $(INC)

net.a: $(OBJ)/framework_net_TCPServer_cpp.o $(OBJ)/framework_net_StreamServer_cpp.o $(OBJ)/framework_net_Gnet_c.o
	ar -crsv $@ $^
