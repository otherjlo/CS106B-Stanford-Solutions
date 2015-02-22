/*
 * File: ListCompletions.cpp
 * -------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the cell phone mind-reading problem
 * from Assignment #3
 * [TODO: extend the documentation]
 */

#include <iostream>
#include "console.h"
#include "simpio.h"
#include "lexicon.h"
#include "vector.h"
using namespace std;

/* Function prototypes */

void listCompletions(string digits, Lexicon & lex, Vector<string> &possibleWords);
void findAllCombos(string digits, string soFar, Lexicon &lexicon, Vector<string> &allWords);
string digitToString(char digit);
void findAllEndings(string prefix, Lexicon &lexicon, Vector<string> &allWords);
bool hasAnotherWord(string prefix, Lexicon &lexicon);
void printWords(Vector<string> &words);

/* Main program */

int main() {
   Lexicon english("EnglishWords.dat");
   cout << "Cell phone mind-reading problem" << endl;
   while (true) {
      cout << "Enter a set of digits: ";
      string digits = getLine();
      if (digits == "" || digits == "quit") break;
      cout << "The words beginning with those digits are:" << endl;
      Vector<string> possibleWords;
      listCompletions(digits, english, possibleWords);
   }
   return 0;
}

/*
 * Function: listCompletions
 * Usage: listCompletions(digits, lexicon);
 * ----------------------------------------
 * Lists all the words in the lexicon that begin with the letters
 * corresponding to the specified digits on a telephone keypad.
 */

void listCompletions(string digits, Lexicon & lexicon, Vector<string> &possibleWords) {
   findAllCombos(digits, "", lexicon, possibleWords);
   printWords(possibleWords);
}

/*
 * Function: findAllCombos
 * Usage: findALlCombos(digits, soFar, lexicon, allWords);
 * -------------------------------------------------------
 * Finds all words that could be made using a multitap phone
 */
void findAllCombos(string digits, string soFar, Lexicon &lexicon, Vector<string> &allWords) {
    //Base Case: No more digits left to transform into strings
    if(digits.size() == 0) {
        //Find all words that contain that prefix
        findAllEndings(soFar, lexicon, allWords);
        return;
    }
    //Get the first digit in digits
    char digit = digits[0];
    //find all letters that are mapped to that digit
    string mappedLetters = digitToString(digit);

    for(int i = 0; i < mappedLetters.size(); i++) {
        //Add that letter to soFar, which is the prefix
        soFar += mappedLetters[i];
        //Recur, to finish the prefix
        findAllCombos(digits.substr(1), soFar, lexicon, allWords);
        //back track, and remove the added letter
        soFar.pop_back();
    }
}

/*
 * Function: digitToString
 * Usage: digitToString(digit);
 * ----------------------------
 * Takes  anumber, and returns a string holding all character mapped to it on a multitap keyboard
 */
string digitToString(char digit) {
    string digString = "";
    //return the string for each number
    switch(digit) {
    case '2': digString = "abc";
        break;
    case '3': digString = "def";
        break;
    case '4': digString = "ghi";
        break;
    case '5': digString = "jkl";
        break;
    case '6': digString = "mno";
        break;
    case '7': digString = "pqrs";
        break;
    case '8': digString = "tuv";
        break;
    case '9': digString = "wxyz";
        break;
    default : digString = " ";
    }
    return digString;
}

/*
 * Function: findAllEndings
 * Usage: findAllEndings(prefix, lexicon, allWords);
 * -------------------------------------------------
 * Prints out each word that could be made from one prefix
 */
void findAllEndings(string prefix, Lexicon &lexicon, Vector<string> &allWords) {
    //Add word if found
    if(lexicon.contains(prefix)) {
        allWords.add(prefix);
    }
    //Base Case: Prefix is not in lexicon
    if(!lexicon.containsPrefix(prefix)) return;

    //Try adding each letter, and see if it is a prefix
    for(char letter = 'a'; letter <= 'z'; letter++) {
        //Add the letter, recur, then remove the letter
        prefix += letter;
        findAllEndings(prefix, lexicon, allWords);
        prefix.pop_back();
    }
}

/*
 * Function: printWords
 * Usage: printWords(words);
 * -------------------------
 * Iterates through a Vector of strings and prints each one
 */
void printWords(Vector<string> &words) {
    for(string word : words) cout<<word<<endl;
}
