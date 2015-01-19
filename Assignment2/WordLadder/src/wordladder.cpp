// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include "console.h"
#include "queue.h"
#include "filelib.h"
#include "stack.h"
#include "set.h"
#include "simpio.h"
#include "vector.h"

//Methods created by me
void welcomePlayer();
void createDictionary();
void playWordLadder();
void readUserInput(string &firstword, string &secondword);
void findWordLadder(string &firstword, string &secondword);
void getNeighbors(string &word, Vector<string> &neighbors, Set<string> &usedWords);
void printLadder(Stack<string> &ladder);

using namespace std;

//Class Variables
Set<string> dictionary;

int main() {
    // TODO: Finish the program!
    welcomePlayer();
    createDictionary();
    playWordLadder();
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

void playWordLadder() {
    string firstword, secondword;
    while(true) {
        readUserInput(firstword, secondword);
        //Game ended, must break
        if(firstword == "" || secondword == "") {
            break;
        }
        findWordLadder(firstword, secondword);
    }
}

/**
 * @brief readUserInput Takes in two string, and assigns them two words user inputs
 * @param firstword String to hold first word that is input
 * @param secondword String to hold second word that is input
 */
void readUserInput(string &firstword, string &secondword) {
    while(true) {
       //Break if first or second word is "Enter"
        firstword = getLine("Word #1 (or Enter to quit): ");
        if(firstword == "")break;
        secondword = getLine("Word #2 (or Enter to quit): ");
        if(secondword == "")break;
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

void findWordLadder(string &firstword, string &secondword) {
    Queue<Stack<string> > ladderQueue;
    Stack<string> origLadder, currLadder;
    Set<string> usedWords;
    string currWord;
    Vector<string> neighbors;

    origLadder.push(firstword);
    ladderQueue.enqueue(origLadder);
    usedWords.add(firstword);

    while(!ladderQueue.isEmpty()) {
        currLadder = ladderQueue.dequeue();
        currWord = currLadder.peek();
        getNeighbors(currWord, neighbors, usedWords);

        for(int index = 0; index < neighbors.size(); index++) {
            string tempword = neighbors[index];
                if(tempword == secondword) {
                    //Print ladder, and exit method entirely
                    currLadder.push(tempword);
                    cout<<"A ladder from "<<secondword<<" back to "<<firstword<<":"<<endl;
                    printLadder(currLadder);
                    return;
                }
                else {
                    Stack<string> templadder = currLadder;
                    templadder.push(tempword);
                    ladderQueue.enqueue(templadder);
                }
            }
        }
    cout<<"No word ladder found from "<<secondword<<" back to "<<firstword<<".";
}


void getNeighbors(string &word, Vector<string> &neighbors, Set<string> &usedWords) {
    for(int index = 0; index < word.size(); index++) {
        for(char letter = 'a'; letter < 'z'; letter++) {
            if(word[index] != letter) {
                string changedword = word;
                changedword[index] = letter;
                if(dictionary.contains(changedword) && !usedWords.contains(changedword)) {
                    neighbors.add(changedword);
                    usedWords.add(changedword);
                }
            }
        }
    }
}

/**
 * @brief printLadder Takes a ladder(Stack) and prints it
 * @param ladder The stack that is a word ladder
 */
void printLadder(Stack<string> &ladder) {
    //While ladder has more than one element, print the element that is popped off
    while(ladder.size() > 1) {
        cout<<ladder.pop()<<" -> ";
    }
    cout<<ladder.pop()<<endl<<endl;
}
