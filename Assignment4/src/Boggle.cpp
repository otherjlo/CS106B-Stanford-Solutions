// This is a .cpp file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include "Boggle.h"
#include "shuffle.h"
#include "random.h"
#include <cmath>

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

Grid<char> board;
Boggle::Boggle(Lexicon& dictionary, string boardText) {
    if(boardText == "") board = createRandomBoard();

}

char Boggle::getLetter(int row, int col) {
    return board.get(row, col);
}

bool Boggle::checkWord(string word) {
    // TODO: implement
    return false;   // remove this
}

bool Boggle::humanWordSearch(string word) {
    // TODO: implement
    return false;   // remove this
}

int Boggle::humanScore() {
    // TODO: implement
    return 0;   // remove this
}

Set<string> Boggle::computerWordSearch() {
    // TODO: implement
    Set<string> result;   // remove this
    return result;        // remove this
}

int Boggle::getScoreComputer() {
    // TODO: implement
    return 0;   // remove this
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
            random.set(row, column, randomChar(currIndex, shuffled));
            currIndex++;
        }
    }
    return random;
}

char Boggle::randomChar(int index, string (&cubes)[16]) {
    string cube = cubes[index];
    string shuffledCube = shuffle(cube);
    int randIndex = randomInteger(0, shuffledCube.length() - 1);
    return shuffledCube[randIndex];
}

int Boggle::boardSize() {
    return board.numRows() * board.numCols();
}
