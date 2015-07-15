/*
 * File: pqueue.cpp (linked-list version)
 * --------------------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file implements the pqueue.h interface using a linked list as the
 * underlying representation.  Only the copy constructor and assignment
 * operator are included.  Your job is to include definitions for the
 * other exported methods.
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
      clear();
      deepCopy(src);
   }
   return *this;
}
