// This is a .h file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#ifndef _boggle_h
#define _boggle_h

#include <iostream>
#include <string>
#include "lexicon.h"
#include "grid.h"
#include "set.h"
#include "vector.h"
using namespace std;

typedef struct dieLocation {
    int row, column;
    bool operator <(const dieLocation &d2) const {
        return row < d2.row ? true : column < d2.column;
    }
}dieLocation;

class Boggle {
public:
    Boggle(Lexicon& dictionary, string boardText);
    char getLetter(int row, int col);
    bool checkWord(string word);
    bool humanWordSearch(string word);
    int humanScore();
    Set<string> computerWordSearch();
    int getScoreComputer();
    int boardSize();
    Set<dieLocation> getLastHighlighted();
    Set<string> getPlayerWords();

    // TODO: add any other member functions/variables necessary

private:
    Grid<char> board;
    Set<string> humanWords;
    Lexicon* dict;
    int playerScore, computerScore;
    Set<dieLocation> lastHumanWord;
    Grid<char> createRandomBoard();
    char randomChar(int index, string (&cubes)[16]);
    Grid<char> createBoard(string cubefaces);
    bool humanWordSearchRecursive(string word, string copy, int letterIndex, Grid<bool> &markedLocations, dieLocation currDie);
    Set<dieLocation> getUnmarkedNeighbors(Grid<bool> &markedLocations, dieLocation currentDie);
    Set<dieLocation> boardAsSet();
    void computerWordSearchRecursive(Set<string> &foundWords, Grid<bool> &markedLocations, string currWord, dieLocation currDie);
};

ostream& operator<<(ostream& out, Boggle& boggle);

#endif // _boggle_h
