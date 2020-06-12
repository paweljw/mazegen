all: mazegen

build/grid.o: grid.cpp grid.h
	g++ -g -Wall -c grid.cpp -o build/grid.o

mazegen: main.cpp maze.h build/grid.o
	g++ main.cpp build/grid.o -o build/mazegen

run: all
	./build/mazegen

clean:
	rm -f build/mazegen
