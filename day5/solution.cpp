#include <iostream>
#include <fstream>
#include <vector>

using namespace std;



class Floor {
    vector<vector<int>> floorMap;
    public:

};

class Line {
    public:
        int x1;
        int y1;
        int x2;
        int y2;
        Line(string in);
};

Line::Line(string in) {
    // input lines always have the form 'x1,y1 -> x2,y2'
    // so find the first space
    int arrowSpace = in.find(' ');
    string sub1 = in.substr(0,arrowSpace);
    string sub2 = in.substr((arrowSpace+4));

    int comma1 = sub1.find(',');
    int comma2 = sub2.find(',');
    x1 = stoi(sub1.substr(0,comma1));
    string test = sub1.substr(comma1);
    y1 = stoi(sub1.substr(comma1+1));
    x2 = stoi(sub2.substr(0,comma2));
    y2 = stoi(sub2.substr(comma2+1));
}

int main(int argc, char *argv[]) {
    string fname = argv[1];
    fstream infile = fstream(fname);
    vector<string> inputLines;
    string line;
    if(infile.is_open()) {
        while (getline(infile, line)) {
            inputLines.push_back(line);
        }
        infile.close();
    }
    vector<Line> lines;
    for (auto l : inputLines) {
        lines.push_back(Line(l));
    }
    cout << "blah\n";
}