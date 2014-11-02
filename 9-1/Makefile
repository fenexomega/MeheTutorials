MXE=i686-pc-mingw32-
CXX=clang++
LD=$(MXE)ld
LD_LIBS= -Bdynamic -lGL -lGLU -lglut -lfreeimage
MXE_LD_LIBS=`i686-pc-mingw32-pkg-config glut freeimage --libs --cflags`
FLAGS=-Wall  

all:
ifeq ($(CROSS),TRUE)
	$(MXE)g++ *.cpp -std=c++11 $(FLAGS) $(MXE_LD_LIBS)
else
	$(CXX) -c *.cpp $(FLAGS) -g 
	$(CXX) *.o -o main $(LD_LIBS)
endif
clean:
	rm *.o *.obj main
