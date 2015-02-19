/*
 * File: CountFifteens.cpp
 * -----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter code for the CountFifteens problem from
 * Assignment #3.
 * [TODO: extend the documentation]
 */

#include <exception>
#include <iostream>
#include <string>
#include "card.h"
#include "console.h"
#include "error.h"
#include "simpio.h"
#include "tokenscanner.h"
#include "vector.h"
using namespace std;

/* Function prototypes */

int countFifteens(Vector<Card> & cards);
int countFifteenCombos(Vector<Card> &cards, int count);
/*
 * Main program
 * ------------
 * This test program does no error-checking on the input.  One of the
 * extensions you might consider is adding code to this program (and
 * possibly to the Card class) to allow the program to report errors.
 */

int main() {
   while (true) {
      string line = getLine("Enter a hand of cards: ");
      if (line == "") break;
      TokenScanner scanner(line);
      scanner.ignoreWhitespace();
      Vector<Card> hand;
      while (scanner.hasMoreTokens()) {
         hand.add(Card(scanner.nextToken()));
      }
      int nWays = countFifteens(hand);
      string plural = (nWays == 1) ? "" : "s";
      cout << nWays << " way" << plural << endl;
   }
   return 0;
}

/*
 * Counts the number of ways of making a total of 15 from the vector of
 * cards.
 */

int countFifteens(Vector<Card> & cards) {
    return countFifteenCombos(cards, 0);
}

/**
 * @brief countFifteenCombos Count the number of ways to make 15 from a hand of cards
 * @param cards the hand used
 * @param count The initial value of the first card
 * @return Number of ways to make 15
 */
int countFifteenCombos(Vector<Card> &cards, int count) {
    //Base Case : Passed over 15, no need to continue
    if(count > 15) return 0;
    //Base Case : Rwached 15, found a solution, return 1 to the combos
    else if(count == 15) return 1;

    int nCombos = 0, combos;
    //Iterate through each remaining card, if none, we reached another "base case", and we just skip over and return 0
    for(int i = 0; i < cards.size(); i++) {
        //Get the card at i, and create a temp vector holding all the ones after
        Card currCard = cards.get(i);
        Vector<Card> temp = cards.subList(i + 1, cards.size() - i - 1);
        //Change Q, J, or K to value 10 if we receive it
        int cardValue = currCard.getRank() > 10 ? 10 : currCard.getRank();
        count += cardValue;
        //Recur, with the next card after i being in front
        int combos = countFifteenCombos(temp, count);
        nCombos += combos;
        //Undo changes to count, so we act like we never had the old cards value we just used
        count -= cardValue;
    }
    return nCombos;
}
