/*
 * File: pqueue.cpp (heap version)
 * -------------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file implements the pqueue.h interface using a heap as the
 * underlying representation.  Only the copy constructor and assignment
 * operator are included.  Your job is to include definitions for the
 * other exported methods and to make a change to the definition of the
 * assignment operator so that it deletes any old storage.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include <string>
#include "error.h"
#include "pqueue.h"
using namespace std;

// TODO: Add your method definitions here

/*
 * Implementation notes: copy constructor and assignment operator
 * --------------------------------------------------------------
 * The constructor and assignment operators follow a standard paradigm,
 * as described in the textbook.
 */

PriorityQueue::PriorityQueue(const PriorityQueue & src) {
   deepCopy(src);
}

PriorityQueue & PriorityQueue::operator=(const PriorityQueue & src) {
   if (this != &src) {
      // TODO: Include code to delete any data from the old queue
      deepCopy(src);
   }
   return *this;
}
