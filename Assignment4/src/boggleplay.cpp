// This is a .cpp file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include "lexicon.h"
#include "Boggle.h"
#include "simpio.h"
#include "bogglegui.h"
#include <cmath>

Boggle getBoard(Lexicon &dict);
void playHumanTurn(Boggle &board, Lexicon &dict);
void printPlayerStats(Boggle &board);
void computerTurn(Boggle &board);
void setComputerWordsGUI(Set<string> &computerWords);
void setGUICubes(Boggle &board);
void printWinner(Boggle &board);
void highlightWord(Boggle &board);

const int ANIMATION_DELAY = 200;

void playOneGame(Lexicon& dictionary) {
    Boggle board = getBoard(dictionary);
    BoggleGUI::initialize(sqrt(board.boardSize()), sqrt(board.boardSize()));
    setGUICubes(board);
    playHumanTurn(board, dictionary);
    computerTurn(board);
    printWinner(board);
}

Boggle getBoard(Lexicon &dict) {
    if(getYesOrNo("Do you want to generate a random board? ")) return Boggle(dict, "");
    string board;
    //true until a proper board is entered (4x4)
    while(true) {
        board = getLine("Enter a 16-character board: ");
        if(board.size() != 16) {
            cout<<"Board must be 16-characters!"<<endl;
        }
        else break;
    }
    return Boggle(dict, toUpperCase(board));
}

void playHumanTurn(Boggle &board, Lexicon& dict) {
    while(true) {
        cout<<board<<endl;
        string input = getLine("Type a word(or Enter to stop): ");
        if(input.empty()) break;
        input = toUpperCase(input);
        //New word, so add to score, set status, and highlight it
        if(board.humanWordSearch(input)) {
            cout<<"You found a new word! \""<<input<<"\" \n\n";
            BoggleGUI::setStatusMessage("You found a new word!" + input);
            highlightWord(board);
            BoggleGUI::recordWord(toLowerCase(input), BoggleGUI::HUMAN);
            BoggleGUI::setScore(board.humanScore(), BoggleGUI::HUMAN);
        }
       //Word to small
        else if(input.size() < 4) {
            cout<<"Word must be four letters or greater!\n\n";
            BoggleGUI::setStatusMessage("Word must be four letters or greater!");
        }
        //Word already found
        else if(board.getPlayerWords().contains(input)) {
            cout<<"Already found that word!\n\n";
            BoggleGUI::setStatusMessage("Already found that word!");
        }
        //Word does not exist
        else if(!dict.contains(input)) {
            cout<<"That is not an English word!\n\n";
            BoggleGUI::setStatusMessage("That is not an English word!");
        }
        //Word is not on board, but does exist
        else {
            cout<<"That word does not exist on this board!\n\n";
            BoggleGUI::setStatusMessage("That word does not exist on this board!");
        }
        printPlayerStats(board);
    }
    cout<<endl;
}

void printPlayerStats(Boggle &board) {
    Set<string> wordsSoFar = board.getPlayerWords();
    cout<<"Your words ("<<wordsSoFar.size()<<"): "<<wordsSoFar<<endl;
    cout<<"Your score: "<<board.humanScore()<<endl<<endl;

}

void computerTurn(Boggle &board) {
    cout<<"It's my turn!"<<endl;
    Set<string> computerWords = board.computerWordSearch();
    setComputerWordsGUI(computerWords);
    BoggleGUI::setScore(board.getScoreComputer(), BoggleGUI::COMPUTER);
    cout<<"My words ("<<computerWords.size()<<"): "<<computerWords<<endl;
    cout<<"My score: "<<board.getScoreComputer()<<endl;
}


void setComputerWordsGUI(Set<string> &computerWords) {
    for(string word : computerWords) {
        BoggleGUI::recordWord(word, BoggleGUI::COMPUTER);
    }
}

void setGUICubes(Boggle &board) {
    for(int row = 0; row < sqrt(board.boardSize()); row++) {
        for(int col = 0; col < sqrt(board.boardSize()); col++) {
            //Set each letter, unhighlighted
            BoggleGUI::labelCube(row, col, board.getLetter(row, col), false);
        }
    }
}

void printWinner(Boggle &board) {
    //Human wins if true
    if(board.humanScore() > board.getScoreComputer()) {
        cout<<"You win this time! Next time, it won't be so easy!\n\n";
        BoggleGUI::setStatusMessage("You win this time! Next time, it won't be so easy!");
        return;
    }
    cout<<"Ha ha ha, I destroyed you. Better luck next time, puny human!\n\n";
    BoggleGUI::setStatusMessage("Ha ha ha, I destroyed you. Better luck next time, puny human!");
}

void highlightWord(Boggle &board) {
    Queue<dieLocation> word = board.getLastHighlighted();
    BoggleGUI::setAnimationDelay(ANIMATION_DELAY);
    //While there is another letter, highligh its location
    while(!word.isEmpty()) {
        dieLocation location = word.dequeue();
        BoggleGUI::setHighlighted(location.row, location.column, true);
    }
    BoggleGUI::clearHighlighting();
}
