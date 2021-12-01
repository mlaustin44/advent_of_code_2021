#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

vector<int> readFile(string fname) {
	vector<int> result;
    int currentline;
	string line;
	ifstream inputFile(fname);
	if (inputFile.is_open()) {
		while (getline(inputFile, line)) {
			currentline = stoi(line);
			result.push_back(currentline);
		}
		inputFile.close();
	}
	return result;
}

vector<int> calculateWindows(vector<int> values) {
    vector<int> windowResult;
    for (int i=0; i < values.size()-2; i++) {
        int window = values[i] + values[i+1] + values[i+2];
        windowResult.push_back(window);
    }
    return windowResult;
}

int main(int argc, char *argv[]) {
	vector<int> values = readFile(argv[1]);
	vector<int> windows = calculateWindows(values);
    int result = 0;
    for (int i=0; i<(windows.size()-1); i++) {
        // cout << "win[i]: " << windows[i] << " win[i+1]: " << windows[i+1] << " result: " << result << "\n";
        if (windows[i] < windows[i+1]) { result++; }
    }
    cout << "Result is: " << result << "\n";
}
