all: run

run: solution
	./solution.o input

runtest: solution
	./solution.o testinput

solution: solution.cpp
	g++ -std=c++17 solution.cpp -o solution.o

clean:
	rm solution.o
