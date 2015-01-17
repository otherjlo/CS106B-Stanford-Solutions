// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include "console.h"

//Methods created by me
void WelcomePlayer();

using namespace std;

int main() {
    // TODO: Finish the program!
    WelcomePlayer();

    cout << "Have a nice day." << endl;
    return 0;
}

/**
 * @brief WelcomePlayer Prints the welcoming message for the Word Ladder program
 */
void WelcomePlayer() {
    cout<<"Welcome to the CS 106B Word Ladder." << endl;
    cout<<"Please give me two English words, and I will change the"<<endl;
    cout<<"first into the second by changing one letter at a time."<<endl<<endl;
}
