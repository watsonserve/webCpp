
INC = ../../include
SRC = ../framework

a.out: th.o event.o test.cpp
	g++ -I $(INC) $^ -lpthread -o $@

th.o: $(SRC)/thread/ThreadPool.cpp
	g++ -c -I $(INC) $^ -o $@

event.o: $(SRC)/Event/Event.cpp
	g++ -c -I $(INC) $^ -o $@

clean:
	rm th.o
	rm event.o
