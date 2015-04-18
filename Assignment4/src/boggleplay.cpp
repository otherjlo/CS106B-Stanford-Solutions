// This is a .cpp file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include "lexicon.h"
#include "Boggle.h"
#include "simpio.h"

Boggle getBoard(Lexicon &dict);
void playHumanTurn(Boggle &board);
void printPlayerStats(Boggle &board);

void playOneGame(Lexicon& dictionary) {
    Boggle board = getBoard(dictionary);
    playHumanTurn(board);
    string human = "human";
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

void playHumanTurn(Boggle &board) {
    while(true) {
        cout<<board<<endl;
        string input = getLine("Type a word(or Enter to stop): ");
        if(input.empty()) break;
        input = toUpperCase(input);
        if(board.humanWordSearch(input)) cout<<"You found a new word! \""<<toUpperCase(input)<<"\""<<endl;
        else if(input.size() < 4) cout<<"Word must be four letters or greater!"<<endl;
        else if(board.getPlayerWords().contains(input))cout<<"Already found that word!"<<endl;
        else cout<<"That word does not exist on this board!"<<endl;
        printPlayerStats(board);
    }
}

void printPlayerStats(Boggle &board) {
    Set<string> wordsSoFar = board.getPlayerWords();
    cout<<"Your words ("<<wordsSoFar.size()<<"): "<<wordsSoFar<<endl;
    cout<<"Your score: "<<board.humanScore()<<endl<<endl;

}
