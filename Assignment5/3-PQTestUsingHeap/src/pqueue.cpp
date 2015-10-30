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
    if(heapsize >= capacity) {
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

/**
 * @brief getLeftChildIndex
 * @param index parent index
 * @return Left child of index
 */
int getLeftChildIndex(int index) {
    return (index * 2) + 1;
}
/**
 * @brief getRightChildIndex
 * @param index Parent index
 * @return Right child of index
 */
int getRightChildIndex(int index) {
    return (index * 2) + 2;
}

/**
 * @brief PriorityQueue::bubbleDown Perform bubbleDown algorithm to sort a heap
 * @param index Root on first level, min child index on all other levels
 */
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
    //If greater than child, swap. and recur
    if(heap[minIndex].priority <= heap[index].priority) {
        Entry temp = heap[index];
        heap[index] = heap[minIndex];
        heap[minIndex] = temp;
        bubbleDown(minIndex);
    }
}

/**
 * @brief PriorityQueue::peek
 * @return Priority of first element
 */
string PriorityQueue::peek() {
    if(size() == 0) error("Cannot call peek on an empty PriorityQueue!");
    return heap[0].value;
}

/**
 * @brief PriorityQueue::peekPriority
 * @return value of first element
 */
double PriorityQueue::peekPriority() {
    if(size() == 0) error("Cannot call peekPriority on an empty PriorityQueue!");
    return heap[0].priority;
}

/**
 * @brief PriorityQueue::isEmpty
 * @return true if pqueue is empty
 */
bool PriorityQueue::isEmpty() {
    return size()==0;
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
      deepCopy(src);
   }
   return *this;
}
