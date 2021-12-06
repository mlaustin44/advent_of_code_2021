#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

vector<int> getStateDay(vector<int> startState, int day) {
    vector<int> state = startState;
    for (int i=0; i<day; i++) {
        int startSize = state.size();
        for (int j=0; j<startSize; j++) {
            if (state[j] == 0) {
                state.push_back(8);
                state[j] = 6;
            } else {
                state[j] -= 1;
            }
        }
    }
    return state;
}

int main(int argc, char *argv[]) {
    string fname = argv[1];
    fstream infile = fstream(fname);
    string rawIn;
    vector<int> startState;
    if (infile.is_open()) {
        // only ever one line in the input
        getline(infile, rawIn);
        infile.close();
    }
    // split the input into numbers (they're all single digits so every even index is a number)
    //  increment counter by 2 to only get numbers not commas
    for (int i=0; i<rawIn.size(); i+=2) {
        startState.push_back(rawIn[i] - char('0'));
    }
    int targetDay = 80;
    vector<int> finalState = getStateDay(startState, targetDay);
    cout << "On day: " << targetDay << " there are: " << finalState.size() << " fish!\n";
}