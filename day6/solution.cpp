#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

// naive approach for part 1
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

// smart approach for part 2
long long getFishOnDay(vector<int> startState, int day) {
    // define a vector with one element for each fish age
    vector<long long> state(9,0);
    //account for the original fish
    for (int f : startState) {
        state[f] += 1;
    }

    for (int i=0; i<day; i++) {
        // find the number of fish that need to spawn
        long long spawningFish = state[0];
        // slide the rest of the fish down.  
        //      could do this in a loop but there's only 9 operations and 2 are special cases
        state[0] = state[1];
        state[1] = state[2];
        state[2] = state[3];
        state[3] = state[4];
        state[4] = state[5];
        state[5] = state[6];
        state[6] = state[7] + spawningFish;
        state[7] = state[8];
        state[8] = spawningFish;
    }

    // calculate the sum of fish
    long long totalFish = 0;
    for (long d : state) {
        totalFish += d;
    }
    return totalFish;
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
    int targetDay;
    if (argc == 3) {
        targetDay = stoi(argv[2]);
    } else{
        targetDay = 256;
    }
    long long totalFish = getFishOnDay(startState, targetDay);
    cout << "On day: " << targetDay << " there are: " << totalFish << " fish!\n";
}