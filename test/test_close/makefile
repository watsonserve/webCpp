ROOT = ../..
INC = $(ROOT)/include
OBJ = $(ROOT)/dist/objs

srv: srv.c $(OBJ)/framework_net_Gnet_c.o
	gcc -o $@ $^ -I $(INC)

cli: cli.c $(OBJ)/framework_net_Gnet_c.o
	gcc -o $@ $^ -I $(INC)
