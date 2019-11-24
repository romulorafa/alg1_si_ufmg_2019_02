CC=g++
CFLAGS=-c -Wall -pedantic

all: main

main: Grafo.o Blackjack.o main.cpp
	$(CC) Grafo.o Blackjack.o main.cpp -o programa.exe

Blackjack.o: Blackjack.cpp
	$(CC) Blackjack.cpp $(CFLAGS)

Grafo.o: Grafo.cpp
	$(CC) Grafo.cpp $(CFLAGS)

clean:
	rm *.o