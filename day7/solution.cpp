#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <math.h>

using namespace std;

// naive approach for part 1
int findMinFuelPart1(vector<int> startPos) {
    // find the min and max positions the crabs occupy 
    int minPos = 10000;
    int maxPos = 0;

    for (int pos : startPos) {
        if (pos > maxPos) { maxPos = pos; }
        if (pos < minPos) { minPos = pos; }
    }

    int minFuel = 2147483647;
    for (int i=minPos; i<maxPos; i++) {
        int fuel=0;
        for (int pos : startPos) {
            fuel += abs(i - pos);
        }
        if (fuel < minFuel) { minFuel = fuel; }
    }
    return minFuel;
}

int findMinFuelPart2(vector<int> startPos) {
    // find the min and max positions the crabs occupy 
    int minPos = 10000;
    int maxPos = 0;

    for (int pos : startPos) {
        if (pos > maxPos) { maxPos = pos; }
        if (pos < minPos) { minPos = pos; }
    }

    int minFuel = 2147483647;
    for (int i=minPos; i<maxPos; i++) {
        int fuel=0;
        for (int pos : startPos) {
            int posToMove = abs(i - pos);
            // we need the sum of all positive integers below the number of positions to move
            for (int j=1; j<=posToMove; j++) {
                fuel += j;
            }
        }
        if (fuel < minFuel) { minFuel = fuel; }
    }
    return minFuel;
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
    int i=0;
    string buf="";
    while (i<rawIn.size()+1) {
        if (rawIn[i] != ',') {
            buf += rawIn[i];
        } else {
            startState.push_back(stoi(buf));
            buf.clear();
        }
        i++;
    }
    startState.push_back(stoi(buf));    //list doesn't end on a comma, so need to manually add the last value

    int minFuel1 = findMinFuelPart1(startState);
    int minFuel2 = findMinFuelPart2(startState);
    cout << "Minimum fuel required for part 1 : " << minFuel1 << " Minimum fuel required for part 2: " << minFuel2 << "\n";
}