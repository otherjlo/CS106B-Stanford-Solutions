#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include "console.h"
#include "filelib.h"
#include "map.h"
#include "vector.h"
#include "simpio.h"
#include "queue.h"
#include "stack.h"
#include "strlib.h"
#include "random.h"

using namespace std;

//Functions written by me
void welcomePlayer();
void promptFile(ifstream &stream, string prompt);
void getN(int &nVal);
void buildMap(ifstream &stream, int Nval);
void getWords(string &line, Vector<string> &words);
int getNumWords(int nVal);
string generateText(int numWords, int nVal);

//Class variables
Map<string, Vector<string> > wordMap;

int main() {
    ifstream stream;
    int nVal, numWords;
    welcomePlayer();
    promptFile(stream, "Input file name? ");
    getN(nVal);
    buildMap(stream, nVal);
    while(true) {
        //get count, if 0, exit, else generate text
        numWords = getNumWords(nVal);
        if(numWords == 0)break;
        cout<<generateText(numWords, nVal)<<endl<<endl;
    }
    cout << "Exiting." << endl;
    return 0;
}
/**
 * @brief welcomePlayer Prints welcoming message for user
 */
void welcomePlayer() {
    cout<<"Welcome to the CS 106B Random Writer ('N-Grams')."<<endl;
    cout<<"This program makes random text based on a document."<<endl;
    cout<<"Give me an input file and an 'N' value for groups"<<endl;
    cout<<"of words, and I'll create random text for you."<<endl<<endl;
}

/**
 * @brief promptFile Prompts user to open a file with a set question
 * @param stream
 */
void promptFile(ifstream &stream, string prompt) {
    string filename;
    while(true) {
        filename = getLine(prompt);
        //Break if valid file
        if(openFile(stream, filename)) {
            break;
        }
       //Clear stream and try again
        else {
            stream.clear();
            cout<<"Invalid file; try again."<<endl;
        }
    }
}

/**
 * @brief getN Reads in user input, assigns it to nVal
 * @param nVal Int to hold the number inputted
 */
void getN(int &nVal) {
    while(true) {
        nVal = getInteger("Value of N? ");
        if(nVal >= 2) {
            break;
        }
        cout<< "Enter a value greater than or equal to 2."<<endl;
    }
}

/**
 * @brief buildMap Build a NGram map from a txt file
 * @param stream Stream containing txt file
 * @param nVal The value of N in N-grams
 */
void buildMap(ifstream &stream, int nVal) {
    Vector<string> words, tempVector;
    string word, line;

    //Break when last line is read
    while(true) {
        getline(stream, line);
        if(stream.fail()) break;
        getWords(line, words);
    }

    //Cycle through each word
    for(int index = 0; index < words.size(); index++) {
        string key;
        //Find all words that follow it
        for(int i = 0; i < nVal; i++) {
            int newIndex;
            tempVector.clear();
            //if index + i is greater than size find the remainder of that num / the words.size, which is always less than or equals to words.size
            if(index + i >= words.size()) {
                newIndex = (index  + i) % (words.size());
            }
            //index is inbounds
            else {
                newIndex = index + i;
            }
            //if last word
            if(i == nVal - 1) {
                key = trimEnd(key);
                //if word exists, get old vector, add last word to it
                if(wordMap.containsKey(key)) {
                    word = words.get(newIndex);
                    tempVector = wordMap.get(key);
                    tempVector.add(word);
                    wordMap.put(key, tempVector);
                }
                //else create new vector with the word
                else {
                    word = words.get(newIndex);
                    tempVector.add(word);
                    wordMap.put(key, tempVector);
                }
            }
            //Add word to key
            else {
                word = words.get(newIndex);
                key += word + " ";
            }
        }
    }
}

/**
 * @brief getWords Returns all words in a line
 * @param line The line passed
 * @param words A vector containing all words before
 */
void getWords(string &line, Vector<string> &words) {
    int currpos, foundpos;
    string foundWord;
    //if line is not blank
    line = trim(line);
    if(line != "") {
        currpos = 0;
        while(true) {
           //look for white space
            foundpos = line.find(" ", currpos);
            //End line, get last word
            if(foundpos == string::npos) {
                foundWord = line.substr(currpos, string:: npos);
                words.add(foundWord);
                break;
            }
            //Find length between whitespace and beginning word, get the word, set currpos to beginning of new word
            foundWord = line.substr(currpos, foundpos - currpos);
            currpos = foundpos + 1;
            words.add(foundWord);

        }
    }
}

/**
 * @brief getNumWords gets the number of words user wants to generate
 * @param nVal val of n
 * @return the num of words to generate
 */
int getNumWords(int nVal) {
    int numWords;
    while(true) {
        numWords = getInteger("# of random words to generate(0 to quit)");
        //Check if greater than value of n, or is 0
        if(numWords >= nVal || numWords == 0) {
            return numWords;
        }
        else {
            cout<<"Must be at least "<<nVal<<" words."<<endl;
        }
    }
}

/**
 * @brief generateText generates text randomly
 * @param numWords Number of words to generate
 * @param nVal The value of n in NGram
 * @return The generated text in a string
 */
string generateText(int numWords, int nVal) {
    int wordCount = 0;
    string text = "...";
    string nextWord, prefix;
    Vector<string> suffixes, tempVector;

    //get all the keys (prefixes)
    tempVector = wordMap.keys();
    //Get first prefix, add the num words, add it to the text
    prefix = tempVector.get(randomInteger(0, tempVector.size() - 1));
    tempVector.clear();
    wordCount += (nVal - 1);
    text += prefix;

    while(true) {
        //get a list of suffixes, and randomly pick one
        suffixes = wordMap.get(prefix);
        nextWord = suffixes.get(randomInteger(0, suffixes.size() - 1));
        wordCount++;
        text += " " + nextWord;

        //Break if wordcount is reached
        if(wordCount == numWords)break;
        prefix += " " + nextWord;
        getWords(prefix, tempVector);
        //Remove first word in prefix, so that it is n-1 size
        tempVector.remove(0);
        prefix = "";
        //Rebuild prefix and add suffix to end, which is done using a vector
        for(int i = 0; i < tempVector.size(); i++) {
            prefix += tempVector.get(i) + " ";
        }
        //Trim the prefix, so we can find it in the map
        prefix = trim(prefix);
        tempVector.clear();
    }
    //Remove the leftover whitespace
    text = trimEnd(text);
    text += "...";
    return text;
}
