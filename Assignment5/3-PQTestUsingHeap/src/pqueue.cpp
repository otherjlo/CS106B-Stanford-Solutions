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

PriorityQueue::PriorityQueue() {
    //Allocate space for heap, set capacity, and set heapsize to 0
    heap = new Entry[10];
    capacity = 10;
    heapsize = 0;
}

PriorityQueue::~PriorityQueue() {
    //clear heap
    delete[] heap;
}

void PriorityQueue::enqueue(string value, double priority) {
    //Set as root if empty
    if(size() == 0) {
        heap[0] = Entry{priority, value};
        heapsize++;
        return;
    }
    //Expand if full
    if(heapsize == capacity) {
        expandCapacity();
    }
    //Create new entry and insert
    Entry newEntry{priority, value};
    bubbleUp(newEntry, heapsize);
    heapsize++;

}
/**
 * @brief getParentIndex Find parent index of a child node
 * @param index Index of child
 * @return Parent index of said child node
 */
int getParentIndex(int index) {
    return (index - 1)/2;
}

/**
 * @brief PriorityQueue::bubbleUp Perform bubbleUp algo
 * @param entry entry to be inserted
 * @param index current index to be swapped with parent
 */
void PriorityQueue::bubbleUp(Entry entry, int index) {
   heap[index] = entry;
   int parentIndex = getParentIndex(index);
   //While parent is greater than child and is not root
   while(heap[index].priority < heap[parentIndex].priority && index > 0) {
       //Swap parent and child, set child index to parent to advance upwards
       heap[index] = heap[parentIndex];
       heap[parentIndex] = entry;

       index = parentIndex;
       parentIndex = getParentIndex(index);
   }
}
/**
 * @brief PriorityQueue::size
 * @return Size of pqueue
 */
int PriorityQueue::size() {
    return heapsize;
}
/**
 * @brief PriorityQueue::clear
 * Clear heap and reset size
 */
void PriorityQueue::clear() {
    //clear data and reset size counter
    delete[] heap;
    heap = new Entry[10];
    capacity = 10;
    heapsize = 0;
}

string PriorityQueue::dequeue() {
    if(size() == 0) error("Cannot call dequeue on an empty heap!");
    string value = heap[0].value;
    //Assign root to last value
    heapsize--;
    heap[0] = heap[size()];
    if(size() > 0) bubbleDown(0);
    return value;
}

int getLeftChildIndex(int index) {
    return (index * 2) + 1;
}
int getRightChildIndex(int index) {
    return (index * 2) + 2;
}


void PriorityQueue::bubbleDown(int index) {
    int leftChildIndex, rightChildIndex, minIndex;
    //Find left and right child index
    leftChildIndex = getLeftChildIndex(index);
    rightChildIndex = getRightChildIndex(index);
    //Right child does nto exist
    if(rightChildIndex >= heapsize) {
        //Left child does not exist
        if(leftChildIndex >= heapsize) {
            return;
        }
        //Left child is leaf
        else minIndex = leftChildIndex;
    }
    else {
        //Choose between left child and right child
        minIndex = heap[leftChildIndex].priority <= heap[rightChildIndex].priority ? leftChildIndex : rightChildIndex;
    }
    if(heap[minIndex].priority <= heap[index].priority) {
        Entry temp = heap[index];
        heap[index] = heap[minIndex];
        heap[minIndex] = temp;
        bubbleDown(minIndex);
    }
}

string PriorityQueue::peek() {
    if(size() == 0) error("Cannot call peek on an empty PriorityQueue!");
    return heap[0].value;
}

double PriorityQueue::peekPriority() {
    if(size() == 0) error("Cannot call peekPriority on an empty PriorityQueue!");
    return heap[0].priority;
}

bool PriorityQueue::isEmpty() {
    return size()==0;
}

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
