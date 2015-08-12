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

PriorityQueue::PriorityQueue() {
    listsize = 0;
    list = NULL;
}

PriorityQueue::~PriorityQueue() {
    clear();
}


int PriorityQueue::size() {
    return listsize;
}

void PriorityQueue::clear() {
    while(list != NULL) {
        Entry* temp = list->next;
        delete list;
        list = temp;
    }
}

bool PriorityQueue::isEmpty() {
    return size() == 0;
}

string PriorityQueue::peek() {
    if(size() == 0) error("Cannot call peek() on an empty PriorityQueue!");
    return list->value;
}

double PriorityQueue::peekPriority() {
    if(size() == 0) error("Cannot call peekPriority() on an empty PriorityQueue!");
    return list->priority;
}

string PriorityQueue::dequeue() {
    if(size() == 0) error("Cannot call dequeue() on an empty PriorityQueue!");
    Entry* next = list->next;
    string value = list ->value;
    delete list;
    list = next;
    return value;
}

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
