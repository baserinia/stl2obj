CXX = g++-6
RM = rm -f
CPPFLAGS = -O3

all: stl2obj

stl2obj : stl2obj.o importstl.o
	$(CXX) -o stl2obj stl2obj.o importstl.o

stl2obj.o : stl2obj.cpp importstl.cpp vectornd.h geometry.h
	$(CXX) -c stl2obj.cpp

importstl.o : importstl.cpp importstl.h
	$(CXX) -c importstl.cpp


clean :
	$(RM) stl2obj importstl.o
