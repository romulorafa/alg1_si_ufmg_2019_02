CC=g++
CFLAGS=-c -Wall -pedantic

all: main

main: Viagem.o main.cpp
	$(CC) Viagem.o main.cpp -o tp2
	$(CC) Viagem.o main.cpp -o tp2.exe

Viagem.o: Viagem.cpp
	$(CC) Viagem.cpp $(CFLAGS)

clean:
	rm *.o