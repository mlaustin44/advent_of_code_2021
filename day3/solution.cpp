#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <cmath>

using namespace std;

vector<string> readFile(string fname) {
    ifstream inputFile(fname);
    string line;
    vector<string> data;
    if (inputFile.is_open()) {
        while(getline(inputFile, line)) {
            data.push_back(line);
        }
        inputFile.close();
    }
    return data;
}

int binToInt(vector<int> in, bool invert) {
    int nDigits = in.size();
    int result = 0;
    for (int i=0; i<nDigits; i++) {
        // need to work in reverse (lsb->msb)
        int j = nDigits - i - 1;
        int v = in[j];
        // invert the bits if we're calculating epsilon
        if (invert) { v = abs(v - 1); }
        // multiply bit by 2^i where is the number of places from the right
        result += v * (1 << i);
    }
    return result;
}

int binToInt(string in) {
    int nDigits = in.size();
    int result = 0;
    for (int i=0; i<nDigits; i++) {
        // need to work in reverse (lsb->msb)
        int j = nDigits - i - 1;
        int v = (in[j] - char('0'));
        // multiply bit by 2^i where is the number of places from the right
        result += v * (1 << i);
    }
    return result;
}

// return the gamma and epsilon numbers calculated for the input
pair<int, int> calculatePart1(vector<string> input) {
    // get the size of the input (all the same size, so get length of first element)
    int inputSize = input[0].size();
    vector<int> result;
    for (int i=0; i < inputSize; i++) {
        int n0 = 0;
        int n1 = 0;
        for (int j=0; j<input.size(); j++) {
            (input[j][i] == '1') ? n1++ : n0++;
        }
        result.push_back((n0 > n1) ? 0 : 1);
    }
    int gamma = binToInt(result, false);
    int epsilon = binToInt(result, true);

    return make_pair(gamma, epsilon);
}

pair<int, int> calculatePart2(vector<string> input) {
    // use the same process as in part 1 to calculate the least and most common values in each position
    int inputSize = input[0].size();

    vector<string> o2_vec = input;
    vector<string> co2_vec = input;
    // iterate through each char in the input, deleting failing entries as we go
    int i = 0;
    while (o2_vec.size() > 1) {
        int most_com;
        // find the most common
        int n1=0, n0=0;
        for (int j=0; j<o2_vec.size(); j++) {
            (o2_vec[j][i] == '1') ? n1++ : n0++;
        }
        if (n1 >= n0) { most_com = 1; } else { most_com = 0; }
        //now drop all of the non-matching values from the array to get the O2
        int k = 0;
        while (k < o2_vec.size()) {
            if ((o2_vec[k][i] - char('0')) != most_com) { 
                o2_vec.erase(o2_vec.begin() + k); 
                k--; //need to drop the index by 1 since we just deleted it
            }
            k++;
        }
        i++;
    }
    // now do the same but for the least common value and CO2
    i = 0;
    while (co2_vec.size() > 1) {
        int least_com;
        // find the least common
        int n1=0, n0=0;
        for (int j=0; j<co2_vec.size(); j++) {
            (co2_vec[j][i] == '1') ? n1++ : n0++;
        }
        if (n1 >= n0) { least_com = 0; } else { least_com = 1; }
        //now drop all of the non-matching values from the array to get the CO2
        int k = 0;
        while (k < co2_vec.size()) {
            if ((co2_vec[k][i] - char('0')) != least_com) { 
                co2_vec.erase(co2_vec.begin() + k); 
                k--; //need to drop the index by 1 since we just deleted it
            }
            k++;
        }
        i++;
    }
    int o2 = binToInt(o2_vec[0]);
    int co2 = binToInt(co2_vec[0]);
    return make_pair(o2, co2);
}
int main(int argc, char *argv[]) {
    vector<string> input = readFile(argv[1]);
    pair<int, int> part1result = calculatePart1(input);
    int part1product = part1result.first * part1result.second;
    cout << "Part 1\n\tGamma: " << part1result.first << " Epsilon: " << part1result.second << " Product: " << part1product << "\n";
    pair<int, int> part2result = calculatePart2(input);
    int part2product = part2result.first * part2result.second;
    cout << "Part 2\n\tO2: " << part2result.first << " CO2: " << part2result.second << " Product: " << part2product << "\n";
}