/*
 * File: pqueue.cpp (array version)
 * --------------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file implements the pqueue.h interface using a dynamic array as
 * the underlying representation.  Most of the code is already in place.
 * The only thing that is missing is the implementation of the actual
 * commands.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include <string>
#include "error.h"
#include "pqueue.h"
using namespace std;

PriorityQueue::PriorityQueue() {
   // TODO: Fill in the necessary code
}

PriorityQueue::~PriorityQueue() {
   // TODO: Fill in the necessary code
}

int PriorityQueue::size() {
   return 0;  // TODO: Replace this line with the necessary code
}

bool PriorityQueue::isEmpty() {
   return true;  // TODO: Replace this line with the necessary code
}

void PriorityQueue::clear() {
   // TODO: Fill in the necessary code
}

void PriorityQueue::enqueue(string value, double priority) {
   // TODO: Fill in the necessary code
}

string PriorityQueue::dequeue() {
   return "";  // TODO: Replace this line with the necessary code
}

string PriorityQueue::peek() {
   return "";  // TODO: Replace this line with the necessary code
}

double PriorityQueue::peekPriority() {
   return 0;  // TODO: Replace this line with the necessary code
}

/*
 * Implementation notes: copy constructor and assignment operator
 * --------------------------------------------------------------
 * The constructor and assignment operators follow the standard
 * paradigm described in the textbook.
 */

PriorityQueue::PriorityQueue(const PriorityQueue & src) {
   deepCopy(src);
}

PriorityQueue & PriorityQueue::operator=(const PriorityQueue & src) {
   if (this != &src) {
      if (array != NULL) delete[] array;
      deepCopy(src);
   }
   return *this;
}
