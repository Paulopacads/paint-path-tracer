CC=g++
CFLAGS=-std=c++20 -pedantic -O3 -fopenmp

BIN=ppt
SRC=$(wildcard src/*.cpp)
OBJ=$(SRC:.cpp=.o)
MAIN=main.cpp

all: paint_pathtracer

paint_pathtracer: main.o $(OBJ)
	$(CC) $(CFLAGS) $^ -o $(BIN)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(BIN) $(OBJ) main.o $(DEPS)
