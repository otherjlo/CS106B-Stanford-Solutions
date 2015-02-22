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

void listCompletions(string digits, Lexicon & lex);
void findAllCombos(string digits, string soFar, Lexicon &lexicon, Vector<string> &allWords);
string digitToString(char digit);
void findAllEndings(string prefix, Lexicon &lexicon, Vector<string> &allWords);
bool hasAnotherWord(string prefix, Lexicon &lexicon);
/* Main program */

int main() {
   Lexicon english("EnglishWords.dat");
   cout << "Cell phone mind-reading problem" << endl;
   while (true) {
      cout << "Enter a set of digits: ";
      string digits = getLine();
      if (digits == "" || digits == "quit") break;
      cout << "The words beginning with those digits are:" << endl;
      listCompletions(digits, english);
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

void listCompletions(string digits, Lexicon & lexicon) {
   Vector<string> foundWords;
   findAllCombos(digits, "", lexicon, foundWords);
   //Iterate and print each word
   for(string word : foundWords) {
       cout<<word<<endl;
   }
}

/*
 * Function: findAllCombos
 * Usage: findALlCombos(digits, soFar, lexicon, allWords);
 * ---------------------------------------------
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
 * ----------------------------------------
 * Prints out each word that could be made from one prefix
 */
void findAllEndings(string prefix, Lexicon &lexicon, Vector<string> &allWords) {
    //Base Case : Word found. If it is not a prefix of another word, such as (palisade and palisaded) return
    if(lexicon.contains(prefix)) {
        allWords.add(prefix);
        if(!hasAnotherWord(prefix, lexicon)) return;
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
 * Function: hasAnotherWord
 * Usage: hasAnotherWord(prefix, lexicon);
 * ---------------------------------------
 * If a lexicon has a word that begins with the prefix + another letter, return true
 */
bool hasAnotherWord(string prefix, Lexicon &lexicon) {
    //See if adding any other letter is a prefix for another, longer word
    for(char ch = 'a'; ch <= 'z'; ch++) {
        //Add the letter, check if it is a prefix in the lexicon, then remove it
        prefix += ch;
        if(lexicon.containsPrefix(prefix)) return true;
        prefix.pop_back();
    }
    return false;
}
