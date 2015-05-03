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
#include "queue.h"
#include "vector.h"
using namespace std;

/** struct containing row and column of each letter on boggle board */
typedef struct dieLocation {
    int row, column;
    bool operator <(const dieLocation &d2) const {
        return row < d2.row ? true : column < d2.column;
    }
}dieLocation;

class Boggle {
public:
    /**
     * @brief Boggle Creates an instance of Boggle
     * @param dictionary The dictionary boggle will use to find words, and check if they exist.
     * @param boardText The string to represent a Boggle board, "" creates a random board.
     */
    Boggle(Lexicon& dictionary, string boardText);

    /**
     * @brief getLetter Returns the letter at the given row and column, if within bounds.
     * @param row The row to get letter
     * @param col Column to get letter
     * @return Letter at given row and column
     */
    char getLetter(int row, int col);

    /**
     * @brief checkWord Checks if valid word
     * @param word Word to be checked
     * @return If player has not used word, and word is in dictionary, and word is 4 letters or longer
     */
    bool checkWord(string word);

    /**
     * @brief humanWordSearch Finds whether or not a word exists on board
     * @param word The word to be searched for
     * @return Whether word can be made on board
     */
    bool humanWordSearch(string word);

    /**
     * @brief humanScore Player score
     * @return Player score
     */
    int humanScore();

    /**
     * @brief computerWordSearch find all words that player has not found
     * @return Set of all words computer found
     */
    Set<string> computerWordSearch();

    /**
     * @brief getScoreComputer Gets the computer's score
     * @return The computer's score
     */
    int getScoreComputer();

    /**
     * @brief boardSize Rows  * columns
     * @return Num of die on board
     */
    int boardSize();

    /**
     * @brief getLastHighlighted Return last word that was guessed, empty if guess was wrong
     * @return Last guessed word
     */
    Queue<dieLocation> getLastHighlighted();

    /**
     * @brief getPlayerWords All words found by player
     * @return All words found by player
     */
    Set<string> getPlayerWords();

    // TODO: add any other member functions/variables necessary

private:
    Grid<char> board;
    Set<string> humanWords;
    Lexicon* dict;
    int playerScore, computerScore;
    Queue<dieLocation> lastHumanWord;
    Grid<char> createRandomBoard();
    char randomChar(int index, string (&cubes)[16]);
    Grid<char> createBoard(string cubefaces);
    bool humanWordSearchRecursive(string word, int letterIndex, Grid<bool> &markedLocations, dieLocation currDie);
    Set<dieLocation> getUnmarkedNeighbors(Grid<bool> &markedLocations, dieLocation currentDie);
    Set<dieLocation> boardAsSet();
    void computerWordSearchRecursive(Set<string> &foundWords, Grid<bool> &markedLocations, string currWord, dieLocation currDie);
    void addToScore(int amount, bool player);
};

ostream& operator<<(ostream& out, Boggle& boggle);

#endif // _boggle_h
