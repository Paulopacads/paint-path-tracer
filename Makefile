CC=g++
CFLAGS= -g -Wall -Wextra -std=c++20 -pedantic -fopenmp

BIN=ppt
SRC=$(wildcard src/*.cpp) $(wildcard libs/*.cpp)
OBJ=$(SRC:.cpp=.o)
MAIN=main.cpp

all: paint_pathtracer

paint_pathtracer: main.cpp $(SRC)
	$(CC) $(CFLAGS) $^ -o $(BIN) -O3

clean:
	$(RM) $(BIN) $(OBJ) main.o $(DEPS)
