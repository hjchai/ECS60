all: main timetest
main: main.o puzzle.o
	g++ -o solver.out main.o puzzle.o
timetest: timetest.o
	g++ -o a.out timetest.o
main.o: main.cpp
	g++ -c main.cpp
puzzle.o: puzzle.cpp
	g++ -c puzzle.cpp
timetest.o: timetest.cpp
	g++ -c timetest.cpp
clean: rm -rf *.o
