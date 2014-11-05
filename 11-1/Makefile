CC=clang++
CFLAGS= -Wall -g
LIBS= -lglut -lGL -lGLU -lm -lfreeimage

all: build run

run:
	./program.out

build:
	$(CC) -o program.out *.cpp $(CFLAGS) $(LIBS)


clean:
	rm *.o *.out
