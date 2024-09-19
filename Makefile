CXX = g++
CXXFLAGS = -Wall -std=c++11

OBJECTS = node.o list.o nqueens.o

nqueens: $(OBJECTS)
	$(CXX) -g $(CXXFLAGS) -o nqueens list.o nqueens.o node.o

list.o: list.cpp list.h node.cpp node.h
	$(CXX) -g $(CXXFLAGS) -c list.cpp

node.o: node.cpp node.h
	$(CXX) -g $(CXXFLAGS)	-c node.cpp

nqueens.o: list.cpp list.h nqueens.cpp node.cpp node.h
	$(CXX) -g $(CXXFLAGS) -c nqueens.cpp	
clean: 
	rm -f *.o NQueens
