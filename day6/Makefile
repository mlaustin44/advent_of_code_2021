all: run

run: solution
	./solution.o input $(day)

runtest: solution
	./solution.o testinput $(day)

solution: solution.cpp
	g++ -std=c++17 solution.cpp -o solution.o

debug:
	g++ -std=c++17 -g solution.cpp -o solution.o
	gdb --args solution.o testinput $(day)

clean:
	rm solution.o
