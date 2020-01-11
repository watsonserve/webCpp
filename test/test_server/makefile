a.out: main.o MsgServer.o ../../dist/objs/framework_Exception_Exception_cpp.o net.a ../../dist/lib/libEvent.a ../../dist/lib/libThread.a
	g++ -o $@ $^ -lpthread

main.o: main.cpp
	gcc -c $^ -o $@ -I ../../include

MsgServer.o: MsgServer.cpp
	gcc -c $^ -o $@ -I ../../include

net.a: ../../dist/objs/framework_net_TCPServer_cpp.o ../../dist/objs/framework_net_StreamServer_cpp.o ../../dist/objs/framework_net_Gnet_c.o
	ar -crsv $@ $^
