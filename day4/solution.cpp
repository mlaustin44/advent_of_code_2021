#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class BingoBoard {
    vector<vector<int>> board;
    vector<vector<int>> matches;
    public:
        BingoBoard (vector<string> in);
        bool checkWinner();
        bool addNumber(int n);
        int calculateScore(int n);
};

// construct the bingoboard from an array of strings
BingoBoard::BingoBoard (vector<string> in) {
    for (int i=0; i<5; i++) {
        string line = in[i];
        vector<int> boardLine;
        string buffer = "";
        for (int j=0; j<line.size(); j+=3) {
            int val=0;
            if (line[j] != ' '){
                int c1 = line[j] - char('0');
                val += (10 * c1);
            }
            int c2 = line[j+1] - char('0');
            val += c2;
            boardLine.push_back(val);
        }
        board.push_back(boardLine);
    }
    // create the matches array with 0s
    matches = vector<vector<int>> (
        5, vector<int>(5, 0)
    );
}

// check a board for a number n and mark the match array if that number is present
bool BingoBoard::addNumber(int n) {
    bool contained = false;
    for (int i=0; i<5; i++) {
        for (int j=0; j<5; j++) {
            if (board[i][j] == n) {
                matches[i][j] = 1;
                contained = true;
            }
        }
    }
    return contained;
}

//check if the board is a winner (either one full row or one full column of matches)
bool BingoBoard::checkWinner() {
    // check rows first
    for (int i=0; i<5; i++) {
        int sumr = 0;
        int sumc = 0;
        for (int j=0; j<5; j++) {
            sumr += matches[i][j];
            sumc += matches[j][i]; //since it's a squre we can calculate in the same loop
        }
        if (sumc == 5 || sumr == 5) {
            return true;
        }
    }
    return false;
}

// calculate the score (product of all unmarked numbers and the last number called)
int BingoBoard::calculateScore(int n) {
    int sumUnmarked = 0;
    for (int i=0; i<5; i++) {
        for (int j=0; j<5; j++) {
            if (matches[i][j] == 0) {
                sumUnmarked += board[i][j];
            }
        }
    }
    return sumUnmarked * n;
}


// helper function to build the array of boards from the messy input
vector<BingoBoard> boardBuilder(vector<string> in) {
    vector<BingoBoard> boards;
    for (int i=0; i<in.size(); i += 6) {
        vector<string> boardIn;
        for (int j=1; j<6; j++) {
            boardIn.push_back(in[i+j]);
        }
        boards.push_back(BingoBoard(boardIn));
    }
    return boards;
}

// helper function to build the array of integers that will be called
vector<int> numBuilder(string in) {
    vector<int> nums;
    string buf;
    for (int i=0; i<in.size(); i++) {
        if (in[i] == ',') {
            nums.push_back( stoi(buf) );
            buf.clear();
        } else {
            buf.push_back(in[i]);
        }
    }
    return nums;
}

int main(int argc, char *argv[]) {
    // read in the file
    string fname = argv[1];
    ifstream inputFile(fname);
    string inputNums;
    vector<string> lines;
    if (inputFile.is_open()) {
        getline(inputFile, inputNums);
        string line;
        while (getline(inputFile, line)) {
            lines.push_back(line);
        }
        inputFile.close();
    }

    // build out arrays of data
    vector<BingoBoard> boards = boardBuilder(lines);
    vector<int> nums = numBuilder(inputNums);

    // loop through all the numbers
    for (int n : nums) {
        // loop through the boards once per number
        for (int j=0; j<boards.size(); j++) {
            // need to get boards by reference not value
            BingoBoard& board = boards[j];
            // check the number, and then if it won calculate the score and drop it from the array
            board.addNumber(n);
            bool won = board.checkWinner();
            if (won) {
                //super lazy approach for part 2 - every time we find a winner, print it and then 
                //  remove that board from the vector.  part 1 answer is the first line of output,
                //  part 2 answer is last line of output
                int score = board.calculateScore(n);
                cout << "Found a winner at board #: " << j << " with score: " << score << "\n";
                boards.erase(boards.begin() + j);
                j--;
            }
        }
    }
}