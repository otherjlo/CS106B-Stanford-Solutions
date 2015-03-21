#include <iostream>
#include <algorithm>
#include "console.h"
#include "vector.h"
#include "simpio.h"
using namespace std;

/* Function prototypes */

int cutStock(Vector<int> & requests, int stockLength);
Vector<int> getSortedVector(Vector<int> &requests);
void cutStockRec(Vector<int> &requests, int stockLength, int remaining, int &count);
bool hasFittingPiece(Vector<int> &requests, int remaining);
int getLargestFit(Vector<int> &requests, int remaining);
/* Main program */

int main() {
   while(true) {
       Vector<int> requests;
       int stockLength = getInteger("Enter pipe length: ");
       //Read in individual requests
       while(true) {
           int stock = getInteger("Enter stock size, 0 to quit: ");
           if(stock == 0) break;
           if(stock > stockLength) cout<<"Cannot enter stock larger than pipe!"<<endl;
           else {
                requests.add(stock);
           }
       }
       cout<<cutStock(requests, stockLength)<<" pipes"<<endl;
   }
   return 0;
}

/*
 * Function: cutStock
 * Usage: int units = cutStock(requests, stockLength);
 * ---------------------------------------------------
 * Computes the minimum number of stock pipes required to satisfy
 * the vector of requests of individual pieces.
 */

int cutStock(Vector<int> & requests, int stockLength) {
   int amount = 0;
   requests = getSortedVector(requests);
   cutStockRec(requests, stockLength, stockLength, amount);
   return amount;
}

/**
 * @brief getSortedVector Sorts a vector of ints by lowest to largest
 * @param requests The vector to be sorted
 * @return The sorted vector
 */
Vector<int> getSortedVector(Vector<int> &requests) {
    //Get standard vector, sort, and copy to new vector
    vector<int> temp = requests.toStlVector();
    sort(temp.begin(), temp.end());
    Vector<int> newVector;
    for(int num : temp) {
        newVector.add(num);
    }
    return newVector;
}

/**
 * @brief cutStockRec Recurs to find minimum amount of pipe needed to fulfill requests
 * @param requests The requests sizes for each cut
 * @param stockLength The length of each pipe
 * @param remaining The amount leftover from each pipe
 * @param count parameter to keep count of amount of pipes used
 */
void cutStockRec(Vector<int> &requests, int stockLength, int remaining, int &count) {
    //No pipes remaining. If we passed the remainder of a pipe, that means we had no left over. else, we need to increment to account for it
    if(requests.isEmpty()) {
        if(remaining != stockLength) count++;
        return;
    }

    if(hasFittingPiece(requests, remaining)) {
       //get best fitting piece, and remove it from both vector and remaining
       int index = getLargestFit(requests, remaining);
       remaining -= requests.get(index);
       requests.remove(index);
       //Full pipe used
       if(remaining == 0) {
           count++;
           cutStockRec(requests, stockLength, stockLength, count);
       }
       //Pipe leftover
       else {
           cutStockRec(requests, stockLength, remaining, count);
       }
    }
    //have to start a new pipe
    else {
        count++;
        cutStockRec(requests, stockLength, stockLength, count);
    }
}

/**
 * @brief hasFittingPiece Checks if any request is less than or equal to the remaining
 * @param requests The requests remaining
 * @param remaining amount of leftover pipe
 * @return Has a piece that fits
 */
bool hasFittingPiece(Vector<int> &requests, int remaining) {
    return requests.get(0) <= remaining;
}

/**
 * @brief getLargestFit Finds largest piece that can fit in remaining pipe
 * @param requests Remaining requests to get
 * @param remaining The amount of pipe leftoever on current pipe
 * @return Index of the largest piece in vecotr requests
 */
int getLargestFit(Vector<int> &requests, int remaining) {
    int index;
    for(int i = 0; i < requests.size(); i++) {
        if(requests.get(i) <= remaining) index = i;
        //Currect piece is greater than remaining, break
        else {
            break;
        }
    }
    return index;
}
