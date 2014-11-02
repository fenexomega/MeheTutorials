MXE=i686-pc-mingw32-
CXX=g++
LD_LIBS= -Llib -Bdynamic -lGL -lGLU -lglut -lfreeimage
MXE_LD_LIBS=`i686-pc-mingw32-pkg-config glut freeimage --libs --cflags`
FLAGS=-Wall  


test: all run

run:
	./main

all:
ifeq ($(CROSS),TRUE)
	$(MXE)g++ *.cpp -std=c++11 $(FLAGS) $(MXE_LD_LIBS)
else
	$(CXX) -c *.cpp $(FLAGS) -g 
	$(CXX) *.o -o main $(LD_LIBS)
endif
clean:
	rm *.o main
