
CXX = g++
CXXFLAGS = -std=c++23 -Wall -O3 -c -Wextra -Wpedantic -g -march=native -flto

LXXFLAGS = -std=c++23 -march=native -flto

TARGET = main

OBJECTS = main.o board.o

$(TARGET): $(OBJECTS)
	$(CXX) $(LXXFLAGS) $(OBJECTS) -o $(TARGET)

main.o: main.cpp
	$(CXX) $(CXXFLAGS) main.cpp
#board.o: board.cpp board.h
#	$(CXX) $(CXXFLAGS) board.cpp

.PHONY: clean
clean:
	rm -f $(TARGET) $(OBJECTS)
