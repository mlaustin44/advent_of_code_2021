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

by nSegments:
5   2,3,5
6   0,6,9

Part 1 - need to find number of 1,4,7,8 that appear
    each of those has a unique number of segments, so
    we can just ignore the input and find the number
    of outputs with those lengths
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

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

// helper function to alphabetize the segment inputs, which are out of order
string alphabetize(string s) {
    vector<bool> segments(7, false);
    for (int i=0; i<s.size(); i++) {
        int c = (s[i] - char('a'));
        segments[c] = true;
    }
    string ordered = "";
    for (int i=0; i<7; i++) {
        if (segments[i]) {
            ordered += char(97+i); //97 is ascii for 'a'
        }
    }
    return ordered;
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

// helper method - does d1 contain d2?
bool digitContains(string d1, string d2) {
    for (char c : d2) {
        if (d1.find(c) == string::npos) {
            return false;
        }
    }
    return true;
}

// helper method - subtract d2 from d1
string subtractDigit(string d1, string d2) {
    string temp = "";
    for (char c : d1) {
        // if the char from d1 isn't in d1 - add it to our buffer
        if (d2.find(c) == string::npos) {
            temp += c;
        }
    }
    return temp;
}

int part2calculate(vector<Input> inputs) {
    int sum = 0;
    for (auto input : inputs) {
        map<int, string> digitMap;

        for (auto& digit : input.digits) {
            digit = alphabetize(digit);
        }

        for (auto& out : input.outputs) {
            out = alphabetize(out);
        }

        // we know 4 digits automatically - the ones with unique # of segments
        // set up vectors for size 5 and 6, which are the remaining cahses
        vector<string> digits5, digits6;
        for (auto digit : input.digits) {
            int dSize = digit.size();
            switch (dSize) {
                case 2:
                    digitMap[1] = digit;
                    break;
                case 3:
                    digitMap[7] = digit;
                    break;
                case 4:
                    digitMap[4] = digit;
                    break;
                case 7:
                    digitMap[8] = digit;
                    break;
                case 5:
                    digits5.push_back(digit);
                    break;
                case 6:
                    digits6.push_back(digit);
                    break;
            }
        }

        // solve for the digits with 5 segments.  we know:
        //  if the digit contains the 1 digit segemnts -> 3
        //  if the digit contains the 4 digit segments minus the 1 digit segments -> 5
        //  the remaining digit is 2
        string fourminusone = subtractDigit(digitMap[4], digitMap[1]);
        for (auto digit: digits5) {
            if (digitContains(digit, digitMap[1])) {
                digitMap[3] = digit;
            } else if (digitContains(digit, fourminusone)) {
                digitMap[5] = digit;
            } else {
                digitMap[2] = digit;
            }
        }

        // solve for the digits with 6 segments.  we know:
        //  if the digit does not contain 1 -> 6
        //  for the remaining digits, if it contains 3 -> 9
        //  last digit -> 0
        // first loop find the 6 digit
        for (int i=0; i<digits6.size(); i++) {
            if (!digitContains(digits6[i], digitMap[1])) {
                digitMap[6] = digits6[i];
                digits6.erase(digits6.begin() + i);
                break;
            }
        }
        for (auto digit : digits6) {
            if (digitContains(digit, digitMap[3])) {
                digitMap[9] = digit;
            } else {
                digitMap[0] = digit;
            }
        }

        // now that we know the digits, we can figure out what the output actually is
        string result = "";
        for (auto out : input.outputs) {
            // do a reverse lookup in the map
            auto it = find_if(digitMap.begin(), digitMap.end(), [&out](const pair<int, string> &p) {
                return p.second == out;
            });
            int value = it->first;
            result += to_string(value);
        }
        sum += stoi(result);
    }
    return sum;
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
    int part2answer = part2calculate(inputs);
    cout << "Part 2 sum: " << part2answer << "\n";
}