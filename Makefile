CC      = g++
CFLAGS  = -g -Wall
LDFLAGS =
OBJFILES = build/main.o build/grid.o build/maze_presenters/stdout.o build/generators/wilson.o
TARGET  = build/mazegen

.PHONY: all run clean test

all: $(TARGET)

run: all
	./$(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)

build/%.o: %.cpp $(wildcard $<.h)
	$(CC) $(CFLAGS) -c $< -o build/$*.o

clean:
	rm -f $(TARGET) $(OBJFILES)

test:
	echo "Heh"
