CXX=clang++
CFLAGS= -Wall -g
LIBS= -lglut -lGL -lGLU -lfreeimage

all: build run
	
run:
	./program.out
build:
	$(CXX) *.cpp -o program.out $(CFLAGS) $(LIBS)
