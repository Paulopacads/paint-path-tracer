CC=g++
CFLAGS=-g -std=c++20 -pedantic -fopenmp

BIN=ppt
SRC=$(wildcard src/*.cpp)
OBJ=$(SRC:.cpp=.o)
MAIN=main.cpp

all: paint_pathtracer

paint_pathtracer: main.o $(OBJ)
	$(CC) $(CFLAGS) $^ -o $(BIN) -O3

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@ -O3

clean:
	$(RM) $(BIN) $(OBJ) main.o $(DEPS)
