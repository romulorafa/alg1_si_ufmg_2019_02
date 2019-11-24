CC=g++
CFLAGS=-c -Wall -pedantic

all: sudoku

sudoku: sudoku.cpp Grafo.o
	$(CC) Grafo.o sudoku.cpp -o tp3
	$(CC) Grafo.o sudoku.cpp -o tp3.exe

Grafo.o: Grafo.cpp
	$(CC) Grafo.cpp $(CFLAGS)

clean:
	rm *.o
