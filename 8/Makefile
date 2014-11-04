CC=clang++
LD_LIBS= -Llib -Wl,-Bstatic -lSOIL -Wl,-Bdynamic -lGL -lGLU -lglut
FLAGS=-Wall -g 

all:
	$(CC) -c *.cpp $(FLAGS)
	$(CC) *.o -o main.out $(LD_LIBS)

clean:
	rm *.o main
