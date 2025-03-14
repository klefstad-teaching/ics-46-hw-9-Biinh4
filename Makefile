CXX = g++
CXXFLAGS = -ggdb -std=c++20 -Werror -Wextra -Wfatal-errors -pedantic -Iinclude

all: d l

d: src/dijkstras_main.cpp lib/dijkstras.o
	$(CXX) $(CXXFLAGS) src/dijkstras_main.cpp lib/dijkstras.o -o dijkstras_main
l: src/ladder_main.cpp lib/ladder.o
	$(CXX) $(CXXFLAGS) src/ladder_main.cpp lib/ladder.o -o ladder_main

lib:
	mkdir -p lib

lib/dijkstras.o: src/dijkstras.cpp src/dijkstras.h 
	$(CXX) $(CXXFLAGS) -c src/dijkstras.cpp -o lib/dijkstras.o
lib/ladder.o: src/ladder.cpp src/ladder.h 
	$(CXX) $(CXXFLAGS) -c src/ladder.cpp -o lib/ladder.o

clean:
	rm -f lib/*.o ladder_main dijkstras_main