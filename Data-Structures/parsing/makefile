CXX=clang++
CXXFLAGS=-g -std=c++11 -Wall

as: main.o as.o
	g++ -o as main.o as.o

main.o: main.cpp as.h
	g++ -c main.cpp

as.o: as.cpp as.h
	g++ -c as.cpp

clean:
	rm *.o as
