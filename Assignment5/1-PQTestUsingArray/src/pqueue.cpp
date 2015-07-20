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
#include "vector.h"
using namespace std;

typedef struct Entry {
    int priority;
    string value;
}Entry;

Vector<Entry *> *priorityqueue;

PriorityQueue::PriorityQueue() {
    priorityqueue = new Vector<Entry *>();
}

PriorityQueue::~PriorityQueue() {
    for(Entry *currEntry : *priorityqueue) {
        delete currEntry;
        currEntry = NULL;
    }
    delete priorityqueue;
    priorityqueue = NULL;
}

int PriorityQueue::size() {
   return priorityqueue->size();
}

bool PriorityQueue::isEmpty() {
   return priorityqueue->isEmpty();
}

void PriorityQueue::clear() {
    for(Entry *currEntry : *priorityqueue) {
        delete currEntry;
        currEntry = NULL;
    }
}

void PriorityQueue::enqueue(string value, double priority) {
   // TODO: Fill in the necessary code
}

string PriorityQueue::dequeue() {
   return "";  // TODO: Replace this line with the necessary code
}

string PriorityQueue::peek() {
    return priorityqueue->get(0)->value;
}

double PriorityQueue::peekPriority() {
   return priorityqueue->get(0)->priority;
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
