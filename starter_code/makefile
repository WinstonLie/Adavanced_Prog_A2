# Obtained template from https://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/

CC=g++
CFLAGS = -Wall -std=c++14 -O -g
DEPS = %.h
OBJ = Tile.o Node.o Player.o LinkedList.o Game.o SaveLoad.o PlayGame.o 
# tried to make object file for main, but didnt work
# most likely due to lack of header file
%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ) main.cpp
	$(CC) -o $@ $^ $(CFLAGS) 

clean:
	rm $(OBJ)