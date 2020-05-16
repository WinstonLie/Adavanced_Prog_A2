# Obtained template from https://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/

CC=g++
CFLAGS = -Wall -std=c++14 -O -g
DEPS = %.h
OBJ = Tile.o Node.o Player.o LinkedList.o Game.o main.o 

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) 

clean:
	rm $(OBJ)