mazegen: main.cpp maze.h
	g++ main.cpp -o build/mazegen

all: mazegen

run: all
	./build/mazegen

clean:
	rm -f build/mazegen
