CC=clang++
FLAGS=-Llib -ISOIL -Wall -g
LIBS= -Wl,-Bstatic -lSOIL -Wl,-Bdynamic -lGL -lGLU -lglut 

all:
	$(CC) -c *.cpp 
	$(CC) *.o -o main $(FLAGS) $(LIBS)

clean:
	rm *.o main
