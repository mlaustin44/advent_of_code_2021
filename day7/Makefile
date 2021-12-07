all: run

run: solution
	./solution.o input

runtest: solution
	./solution.o testinput

solution: solution.cpp
	g++ -std=c++17 solution.cpp -o solution.o

debug:
	g++ -std=c++17 -g solution.cpp -o solution.o
	gdb --args solution.o testinput

clean:
	rm solution.o
