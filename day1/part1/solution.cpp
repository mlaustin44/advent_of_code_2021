#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int processInput(string fname) {
	// lastline - hold value of previous line for comparison
	// currentline - current value read
	// result - counter for number of lines with increases
	int lastline, currentline, result = 0; 
	string line;
	ifstream inputFile(fname);
	if (inputFile.is_open()) {
		// get the first line and pre-store it in the lastLine buffer
		getline(inputFile, line);
		lastline = stoi(line);
		while (getline(inputFile, line)) {
			currentline = stoi(line);
			if (currentline > lastline) { result++; }
			lastline = currentline;
		}
		inputFile.close();
	}
	return result;
}

int main(int argc, char *argv[]) {
	int result = processInput(argv[1]);
	cout << "Result is: " << result << "\n";
}
