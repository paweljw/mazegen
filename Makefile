CXX      ?= g++
CFLAGS   = -g -Wall -std=c++11
LDFLAGS  = -lncurses
OBJFILES = build/main.o build/grid.o \
					 build/maze_presenters/stdout.o \
					 build/generators/wilson.o \
					 build/maze_presenters/ncurses.o
TARGET   = build/mazegen

.PHONY: all run clean test

all: $(TARGET)

run: all
	./$(TARGET)

$(TARGET): $(OBJFILES)
	$(CXX) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)

build/%.o: %.cpp $(wildcard $<.h)
	$(CXX) $(CFLAGS) -c $< -o build/$*.o

clean:
	rm -f $(TARGET) $(OBJFILES)

test:
	echo "Heh"

todo:
	rg --vimgrep "TODO:" | grep -v "Makefile" | xargs -I{} echo "* {}"

todofile:
	rg --vimgrep "TODO:" | grep -v "Makefile" | xargs -I{} echo "* {}" > TODO
