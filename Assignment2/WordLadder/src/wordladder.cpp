// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include "console.h"
#include "vector.h"
#include "queue.h"
#include "filelib.h"
#include "stack.h"

//Methods created by me
void WelcomePlayer();
void CreateDictionary();
void PrintLadder(Stack<string> &ladder);

using namespace std;

//Class Variables
Vector<string> dictionary;

int main() {
    // TODO: Finish the program!
    WelcomePlayer();
    CreateDictionary();
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

/**
 * @brief createDictionary Takes the class variable dictionary, a vector
 * and adds all words from "dictionary.txt" to the vector.
 */
void CreateDictionary() {
    ifstream dictstream;
    string word;
    openFile(dictstream, "dictionary.txt");
    //While another line of text is available, read it
    while(true) {
        getline(dictstream, word);
        //No more lines exist, so close the dictionary and break from reading in anymore lines
        if(dictstream.fail()) {
            dictstream.close();
            break;
        }
        else {
           dictionary.add(word);
        }
    }
}

/**
 * @brief printLadder Takes a ladder(Stack) and prints it
 * @param ladder The stack that is a word ladder
 */
void PrintLadder(Stack<string> &ladder) {
    //While ladder has more elements, print the element that is popped off
    while(!ladder.isEmpty()) {
        cout<<ladder.pop()<<" ";
    }
    cout<<endl;
}
