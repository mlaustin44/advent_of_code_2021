#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

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

class Floor {
    vector<vector<int>> floorMap;
    public:
        Floor(vector<Line> inLines);
        int getOverlaps();
};

Floor::Floor(vector<Line> inLines) {
    // find the max x and y
    int xmax = 0;
    int ymax = 0;
    for (Line l : inLines) {
        int localXmax = (l.x1 > l.x2) ? l.x1 : l.x2;
        int localYmax = (l.y1 > l.y2) ? l.y1 : l.y2;
        if (localXmax > xmax) { xmax = localXmax; }
        if (localYmax > ymax) { ymax = localYmax; }
    }
    // make the 2d array, fill it with zeros
    floorMap = vector<vector<int>> (ymax+1,
        vector<int> (xmax+1, 0));

    // loop through again.  anywhere the line touches add 1
    for (Line l : inLines) {
        // get the 
        // horizontal line ascending (y1 < y2)
        if (l.x1 == l.x2 && l.y1 < l.y2) {
            for (int i=l.y1; i<(l.y2 + 1); i++) {
                floorMap[i][l.x1] += 1;
            }
        // vertical line descending (y1 > y2)
        } else if (l.x1 == l.x2 && l.y1 > l.y2) {
            for (int i=l.y2; i<(l.y1 + 1); i++) {
                floorMap[i][l.x1] += 1;
            }
        // horizontal line ascending (x1 < x2)
        } else if (l.y1 == l.y2 && l.x1 < l.x2) {
            for (int i=l.x1; i<(l.x2 + 1); i++) {
                floorMap[l.y1][i] += 1;
            }
        // horizontal line descending (x1 > x2)
        } else if (l.y1 == l.y2 && l.x1 > l.x2) {
            for (int i=l.x2; i<(l.x1 + 1); i++) {
                floorMap[l.y1][i] += 1;
            }
        // diagonal line case
        } else {
            //0=+ direction, 1=-dir
            int xDir = (l.x2 > l.x1) ? 0 : 1;
            int yDir = (l.y2 > l.y1) ? 0 : 1;
            // case 1 - +x, +y
            if (xDir == 0 && yDir == 0) {
                int mag = l.x2 - l.x1 + 1;
                for (int i=0; i<mag; i++) {
                    floorMap[l.y1 + i][l.x1 + i] += 1;
                } 
            // case 2 = -x, +y
            } else if (xDir == 1 && yDir == 0) {
                int mag = l.x1 - l.x2 + 1;
                for (int i=0; i<mag; i++) {
                    floorMap[l.y1 + i][l.x1 - i] += 1;
                } 
            // case 3 = +x, -y
            } else if (xDir == 0 && yDir == 1) {
                int mag = l.x2 - l.x1 + 1;
                for (int i=0; i<mag; i++) {
                    floorMap[l.y1 - i][l.x1 + i] += 1;
                } 
            // case 4 = -x, -y
            } else if (xDir == 1 && yDir == 1) {
                int mag = l.x1 - l.x2 + 1;
                for (int i=0; i<mag; i++) {
                    floorMap[l.y1 - i][l.x1 - i] += 1;
                } 
            }
        }
    }
}

int Floor::getOverlaps() {
    int nOverlaps = 0;
    for (int i=0; i<floorMap.size(); i++) {
        for (int j=0; j<floorMap[0].size(); j++) {
            if (floorMap[i][j] > 1) { nOverlaps++; }
        }
    }
    return nOverlaps;
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
    Floor floor = Floor(lines);
    int overlaps = floor.getOverlaps();
    cout << "Number of overlaps: " << overlaps << "\n";
}