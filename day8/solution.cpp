/*
0   acbefg  6
1   cf      2*
2   acdeg   5
3   acdfg   5
4   bcdf    4*
5   abdfg   5
6   abdefg  6
7   acf     3*
8   abcdefg 7*
9   acbdfg  6

Part 1 - need to find number of 1,4,7,8 that appear
    each of those has a unique number of segments, so
    we can just ignore the input and find the number
    of outputs with those lengths
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

int partOneCount(vector<string> input) {
    return 0;
}

struct Input {
    vector<string> digits;
    vector<string> outputs;
};

// helper function to split strings on spaces
vector<string> splitStringSpaces(string s) {
    vector<string> out;
    int i=0;
    string buf;
    while (i < s.size()) {
        if (s[i] == ' ') {
            out.push_back(buf);
            buf.clear();
        } else {
            buf += s[i];
        }
        i++;
    }
    out.push_back(buf); //no space at EOL, so need to add whatever is left back in
    return out;
}

// helper function to parse a line of raw input into a struct
Input parseInput(string line) {
    vector<string> digits;
    vector<string> outputs;
    Input result;
    // split on the | delimiter
    int delimPos = line.find('|') - 1;
    string dig = line.substr(0,delimPos);
    string out = line.substr(delimPos+3, line.size());
    result.digits = splitStringSpaces(dig);
    result.outputs = splitStringSpaces(out); 

    return result;
}

int part1CountDigits (vector<Input> inputs) {
    int count = 0;
    for (auto in : inputs) {
        for (string o : in.outputs) {
            int osize = o.size();
            if (osize == 2 || osize == 4 || osize == 3 || osize == 7) {
                count++;
            }
        }
    }
    return count;
}

int main(int argc, char *argv[]) {
    //read in the input file
    vector<string> rawLines;
    string line;
    fstream file = fstream(argv[1]);
    if (file.is_open()) {
        while (getline(file, line)) {
            rawLines.push_back(line);
        }
        file.close();
    }
    
    vector<Input> inputs;
    for (auto line : rawLines) {
        Input res = parseInput(line);
        inputs.push_back(res);
    }
    int part1answer = part1CountDigits(inputs);
    cout << "Part 1 count: " << part1answer << "\n";
}