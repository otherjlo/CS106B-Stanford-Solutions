// This is a .cpp file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include "Boggle.h"
#include "shuffle.h"
#include "random.h"
#include <cmath>
#include "set.h"

// letters on all 6 sides of every cube
static string CUBES[16] = {
    "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
    "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
    "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
    "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};

// letters on every cube in 5x5 "Big Boggle" version (extension)
static string BIG_BOGGLE_CUBES[25] = {
   "AAAFRS", "AAEEEE", "AAFIRS", "ADENNN", "AEEEEM",
   "AEEGMU", "AEGMNN", "AFIRSY", "BJKQXZ", "CCNSTW",
   "CEIILT", "CEILPT", "CEIPST", "DDLNOR", "DDHNOT",
   "DHHLOR", "DHLNOR", "EIIITT", "EMOTTT", "ENSSSU",
   "FIPRSY", "GORRVW", "HIPRRY", "NOOTUW", "OOOTTU"
};

Boggle::Boggle(Lexicon& dictionary, string boardText) {
    Boggle::dict = dictionary;
    if(boardText == "") Boggle::board = createRandomBoard();
    else Boggle::board = createBoard(boardText);
    Boggle::playerScore = 0;
    Boggle::computerScore = 0;
}

char Boggle::getLetter(int row, int col) {
    return Boggle::board.get(row, col);
}

bool Boggle::checkWord(string word) {
    return (Boggle::dict.contains(word) && Boggle::humanWords.contains(word) && word.length() >=4);
}

bool Boggle::humanWordSearch(string word) {
    // TODO: implement
    return false;   // remove this
}

int Boggle::humanScore() {
    return Boggle::playerScore;
}

Set<string> Boggle::computerWordSearch() {
    // TODO: implement
    Set<string> result;   // remove this
    return result;        // remove this
}

int Boggle::getScoreComputer() {
    return Boggle::computerScore;
}

ostream& operator<<(ostream& out, Boggle& boggle) {
    for(int row = 0; row < sqrt(boggle.boardSize()); row++) {
        for(int col = 0; col < sqrt(boggle.boardSize()); col++) {
            out<< boggle.getLetter(row, col);
        }
        out<<endl;
    }
    return out;
}

Grid<char> Boggle::createRandomBoard() {
    Grid<char> random(4, 4);
    string shuffled[16] = CUBES;
    shuffle(shuffled, 16);
    int currIndex = 0;
    for(int row = 0; row < random.numRows(); row++) {
        for(int column = 0; column < random.numCols(); column++) {
            //for each die on board, set it to a random letter from the current die
            random.set(row, column, randomChar(currIndex, shuffled));
            currIndex++;
        }
    }
    return random;
}

char Boggle::randomChar(int index, string (&cubes)[16]) {
    string cube = cubes[index];
   //Shuffle and then pick random side
    string shuffledCube = shuffle(cube);
    int randIndex = randomInteger(0, shuffledCube.length() - 1);
    return shuffledCube[randIndex];
}

Grid<char> Boggle::createBoard(string cubefaces) {
    Grid<char> board(4,4);
    int currIndex = 0;
    for(int row = 0; row < board.numRows(); row++) {
        for(int col = 0; col < board.numCols(); col++) {
            //for each die on board, set it to the currIndex in passed string
            board.set(row, col, cubefaces[currIndex]);
            currIndex++;
        }
    }
    return board;
}

int Boggle::boardSize() {
    return Boggle::board.numRows() * Boggle::board.numCols();
}

Set<dieLocation> Boggle::getUnmarkedNeighbors(Grid<bool> &markedLocations, dieLocation currentDie) {
    int row = currentDie.row;
    int column = currentDie.column;
    Set<dieLocation> neighbors;
    for(int currRow = row - 1; currRow < row + 1; currRow++) {
        for(int currCol = column - 1; currCol < column + 1; currCol++) {
            //if neighbor is in bounds, get its row and column.
              if(markedLocations.inBounds(currRow, currCol)) {
              //if neighbor is unmarked, add it to the  neighbors set
                  if(markedLocations.get(currRow, currCol)) {
                    dieLocation neighbor;
                    neighbor.row = currRow;
                    neighbor.column = currCol;
                    neighbors.add(neighbor);
                  }
            }
        }
    }
    return neighbors;
}
