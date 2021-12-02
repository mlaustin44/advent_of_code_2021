#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Position {
    int depth = 0;
    int hpos = 0;    //horizontal position
};

Position positionFromFilePart1(string fname) {
    ifstream inputFile(fname);
    string line;
    Position position;
    if (inputFile.is_open()) {
        while(getline(inputFile, line)) {
            // first let's get the magnitude by taking the last char of the string
            // all the magnitudes are single digits in the input so can do the lazy solution ;-)
            // convert char to int
            int mag = line.back() - char('0');
            // then get the direction, same deal because each of the 3 directions has a different first charecter
            char dir = line.front();
            // cout << "dir: " << dir << " mag: " << mag << "\n";
            switch(dir) {
                case 'd':
                    position.depth += mag;
                    break;
                case 'u':
                    if (position.depth > 0) { position.depth -= mag; }
                    break;
                case 'f':
                    position.hpos += mag;
                    break;
            }
        }
        inputFile.close();
    }
    return position;
}

Position positionFromFilePart2(string fname) {
    ifstream inputFile(fname);
    string line;
    Position position;
    int aim = 0;
    if (inputFile.is_open()) {
        while(getline(inputFile, line)) {
            // first let's get the magnitude by taking the last char of the string
            // all the magnitudes are single digits in the input so can do the lazy solution ;-)
            // convert char to int
            int mag = line.back() - char('0');
            // then get the direction, same deal because each of the 3 directions has a different first charecter
            char dir = line.front();
            // cout << "dir: " << dir << " mag: " << mag << "\n";
            switch(dir) {
                case 'd':
                    aim += mag;
                    break;
                case 'u':
                    aim -= mag;
                    break;
                case 'f':
                    position.hpos += mag;
                    position.depth += (aim * mag);
                    break;
            }
        }
        inputFile.close();
    }
    return position;
}


int main(int argc, char *argv[]) {
    Position result1 = positionFromFilePart1(argv[1]);
    int part1result = result1.depth * result1.hpos;
    cout << "Part 1\n\tFinal depth: " << result1.depth << " horizontal: " << result1.hpos << " product: " << part1result << "\n";

    Position result2 = positionFromFilePart2(argv[1]);
    int part2result = result2.depth * result2.hpos;
    cout << "Part 2\n\tFinal depth: " << result2.depth << " horizontal: " << result2.hpos << " product: " << part2result << "\n";
}