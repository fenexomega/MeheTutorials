CC=clang++
FLAGS= -Wall -g
LIBS= -Llib -ISOIL -Wl,-Bstatic -lSOIL -Wl,-Bdynamic -lGL -lGLU -lglut 

all:
	$(CC) -c *.cpp $(FLAGS)
	$(CC) *.o -o main $(LIBS)

clean:
	rm *.o main
