
INC = ../../include
SRC = ../framework

a.out: th.o test.cpp
	g++ -I $(INC) $^ -lpthread -o $@

th.o: $(SRC)/thread/ThreadPool.cpp
	g++ -c -I $(INC) $^ -o $@

clean:
	rm th.o
