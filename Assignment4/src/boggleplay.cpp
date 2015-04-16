// This is a .cpp file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include "lexicon.h"
#include "Boggle.h"
void playOneGame(Lexicon& dictionary) {
    //notepiaqzzsqrppp
    Boggle game = Boggle(dictionary, "");
    cout<<game<<endl;
    cout<<game.computerWordSearch()<<endl;

}
