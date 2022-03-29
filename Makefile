CC=g++

SRC=$(wildcard src/*.cpp) $(wildcard libs/*.cpp)
OBJ=$(SRC:.cpp=.o)
MAIN=main.cpp

all: raytracer

raytracer: main.o $(OBJ)
	$(CC) $^ -o raytracer -O3


%.o: %.c
	$(CC) -c $< -o $@ -O3

clean:
	-$(RM) raytracer
	-$(RM) $(OBJ)
	-$(RM) main.o
