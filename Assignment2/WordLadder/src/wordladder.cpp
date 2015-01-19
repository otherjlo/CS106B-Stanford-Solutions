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
#include "set.h"
#include "simpio.h"

//Methods created by me
void welcomePlayer();
void createDictionary();
void readUserInput(string &firstword, string &secondword);
void printLadder(Stack<string> &ladder);

using namespace std;

//Class Variables
Set<string> dictionary;

int main() {
    // TODO: Finish the program!
    welcomePlayer();
    createDictionary();
    cout << "Have a nice day." << endl;
    return 0;
}

/**
 * @brief WelcomePlayer Prints the welcoming message for the Word Ladder program
 */
void welcomePlayer() {
    cout<<"Welcome to the CS 106B Word Ladder." << endl;
    cout<<"Please give me two English words, and I will change the"<<endl;
    cout<<"first into the second by changing one letter at a time."<<endl<<endl;
}

/**
 * @brief createDictionary Takes the class variable dictionary, a vector
 * and adds all words from "dictionary.txt" to the vector.
 */
void createDictionary() {
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
 * @brief readUserInput Takes in two string, and assigns them two words user inputs
 * @param firstword String to hold first word that is input
 * @param secondword String to hold second word that is input
 */
void readUserInput(string &firstword, string &secondword) {
    while(true) {
        firstword = getLine("Word #1 (or Enter to quit): ");
        secondword = getLine("Word #2 (or Enter to quit): ");
        //Make words lowercase to be found in dicitonary
        firstword = toLowerCase(firstword);
        secondword = toLowerCase(secondword);
        //Check if words are same
        if(firstword == secondword) {
            cout<<"The two words must be different."<<endl;
        }
       //Check if words are same size
        else if(firstword.size() != secondword.size()) {
            cout<<"The two words must be the same length."<<endl;
        }
        //Check if words are in the dictionary
        else if(!(dictionary.contains(firstword) && dictionary.contains(secondword))) {
            cout<<"The two words must be found in the dictionary."<<endl;
        }
        //Passed all tests, break from the loop
        else {
            break;
        }
    }
}

/**
 * @brief printLadder Takes a ladder(Stack) and prints it
 * @param ladder The stack that is a word ladder
 */
void printLadder(Stack<string> &ladder) {
    //While ladder has more elements, print the element that is popped off
    while(ladder.size() > 1) {
        cout<<ladder.pop()<<" -> ";
    }
    cout<<ladder.pop()<<endl;
}
