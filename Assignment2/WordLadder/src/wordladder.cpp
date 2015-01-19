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
Vector<string> getNeighbors(string &word, Set<string> &usedWords);
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

/**
 * @brief playWordLadder Plays word ladder until user enters "enter
 */
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

/**
 * @brief findWordLadder Uses breadth first search algorithm to find a word ladder
 * @param firstword Word that will lead to other word
 * @param secondword Word to be found
 */
void findWordLadder(string &firstword, string &secondword) {
    //Setup simple data structures
    Queue<Stack<string> > ladderQueue;
    Stack<string> currLadder, tempLadder;
    Set<string> usedWords;
    string currWord, tempWord;
    Vector<string> neighbors;

    //Set up first ladder, push first word to it
    currLadder.push(firstword);
    ladderQueue.enqueue(currLadder);
    usedWords.add(firstword);

    //While a ladder still exists
    while(!ladderQueue.isEmpty()) {
        //Take off top ladder, and get top word off of it
        currLadder = ladderQueue.dequeue();
        currWord = currLadder.peek();
        //Find all neighbors of the currWord
        neighbors = getNeighbors(currWord, usedWords);
       //Go through each neighbor word, and check if it is the secondword
        for(int index = 0; index < neighbors.size(); index++) {
            tempWord = neighbors.get(index);

            if(tempWord == secondword) {
                //Push the final word to the final ladder
                currLadder.push(tempWord);
                cout<<"A ladder from "<<secondword<<" back to "<<firstword<<":"<<endl;
                //Print ladder, exit method
                printLadder(currLadder);
                return;
            }
            //Neighbor is not final word
            else {
                //Copy current ladder to a temp one, and push the word to the temp ladder
                tempLadder = currLadder;
                tempLadder.push(tempWord);
                //Add the new ladder to the queue(ladderQueue)
                ladderQueue.enqueue(tempLadder);
            }
        }
    }
    //No ladder found
    cout<<"No word ladder found from "<<secondword<<" back to "<<firstword<<"."<<endl;
}

/**
 * @brief getNeighbors Returns a vector holding all valid english words with one letter changed from passed word
 * @param word Word to have its neighbors found
 * @param usedWords A set of words that have already been used in all ladders
 * @return A vector holding all neigbors of the passed word
 */
Vector<string> getNeighbors(string &word, Set<string> &usedWords) {
    Vector<string> neighbors;
   //For each letter in word, change the letter
    for(int index = 0; index < word.size(); index++) {
        for(char letter = 'a'; letter <= 'z'; letter++) {
            //Make sure the lettersd are not the same
            if(word[index] != letter) {
                string changedword = word;
                changedword[index] = letter;
               //if word has not been used, and is in the dictionary, is true
                if(dictionary.contains(changedword) && !usedWords.contains(changedword)) {
                    neighbors.add(changedword);
                    usedWords.add(changedword);
                }
            }
        }
    }
    return neighbors;
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
