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

using namespace std;

void welcomePlayer();
void promptFile(ifstream &stream, string prompt);

int main() {
    ifstream stream;
    welcomePlayer();
    promptFile(stream, "Input file name? ");
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
       //Clear strean and try again
        else {
            stream.clear();
            cout<<"Invalid file; try again."<<endl;
        }
    }
}
