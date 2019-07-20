
INC = ../../include
SRC = ../framework

a.out: event.o th.o sem.o test.cpp
	g++ -I $(INC) $^ -lpthread -o $@

th.o: $(SRC)/thread/ThreadPool.cpp
	g++ -c -I $(INC) $^ -o $@

sem.o: $(SRC)/thread/sem.c
	gcc -c -I $(INC) $^ -o $@

event.o: $(SRC)/Event/Event.cpp
	g++ -c -I $(INC) $^ -o $@

clean:
	rm *.o
