/*
 * File: PQTest.cpp
 * ----------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This is the starter file for the test program for Assignment #5.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include "console.h"
#include "pqueue.h"
#include "simpio.h"
#include "strlib.h"
#include "tokenscanner.h"
#include <vector>
using namespace std;

/* Function prototypes */

void helpCommand();
void clearCommand(PriorityQueue &pq);
void sizeCommand(PriorityQueue &pq);
void peekCommand(PriorityQueue &pq);
void peekPriorityCommand(PriorityQueue &pq);
void listCommand(PriorityQueue &pq);
void dequeueCommand(PriorityQueue &pq);
void isEmptyCommand(PriorityQueue &pq);
void enqueueCommand(PriorityQueue &pq, vector<string> &args);

/* Main program */

int main() {
   PriorityQueue pq;

   while (true) {
      string cmd = getLine("> ");
      if (cmd == "help") {
         helpCommand();
      }
      else if(cmd == "clear") {
          clearCommand(pq);
      }
      else if(cmd == "size") {
          sizeCommand(pq);
      }
      else if(cmd == "peek") {
          peekCommand(pq);
      }
      else if(cmd == "list") {
          listCommand(pq);
      }
      else if(cmd == "peekPriority") {
          peekPriorityCommand(pq);
      }
      else if(cmd == "isEmpty") {
          isEmptyCommand(pq);
      }
      else if(cmd == "dequeue") {
          dequeueCommand(pq);
      }
      else if(startsWith(cmd, "enqueue")) {
          vector<string> vec = stringSplit(cmd, " ");
          enqueueCommand(pq, vec);
      }
      else {
         cout << "Undefined command: " << cmd << endl;
      }
   }
   return 0;
}

/*
 * Function: helpCommand
 * ---------------------
 * Displays a list of the required commands.  If you extend this program,
 * you should add new entries to this function.
 */

void helpCommand() {
   cout << "enqueue value priority -- Enqueues value at priority" << endl;
   cout << "dequeue -- Dequeues the most urgent item" << endl;
   cout << "peek -- Peeks at the first item without removing it" << endl;
   cout << "peekPriority -- Reports the priority of the first item" << endl;
   cout << "clear -- Clears the queue" << endl;
   cout << "size -- Reports the size of the queue" << endl;
   cout << "isEmpty -- Reports whether the queue is empty" << endl;
   cout << "list -- Lists the elements of the queue" << endl;
   cout << "help -- Prints this message" << endl;
}

void clearCommand(PriorityQueue &pq) {
    pq.clear();
}

void sizeCommand(PriorityQueue &pq) {
   cout<<pq.size()<<endl;
}

void peekCommand(PriorityQueue &pq) {
    try {
        cout<<pq.peek()<<endl;
    }
    catch(ErrorException &ex) {
        cout<<ex.getMessage()<<endl;
    }
}

void peekPriorityCommand(PriorityQueue &pq) {
    try {
        cout<<pq.peekPriority()<<endl;
    }
    catch(ErrorException &ex) {
        cout<<ex.getMessage()<<endl;
    }
}

void listCommand(PriorityQueue &pq) {
    PriorityQueue copy(pq);
    cout<<"Queue: ";
    while(!copy.isEmpty()) {
        cout<<copy.dequeue()<<" ";
    }
    cout<<endl;
}

void dequeueCommand(PriorityQueue &pq) {
    try {
        cout<<pq.dequeue()<<endl;
    }
    catch(ErrorException &ex) {
        cout<<ex.getMessage()<<endl;
    }
}

void isEmptyCommand(PriorityQueue &pq) {
    string result = pq.isEmpty() ? "true" : "false";
    cout<<result<<endl;
}

void enqueueCommand(PriorityQueue &pq, vector<string> &args) {
    double priority;
    string value;
    if(args.size() != 3) {
        cout<<"Format command as \"enqueue value priority\""<<endl;
        return;
    }
    try {
        priority = stringToReal(args[2]);
        value = args[1];
        pq.enqueue(value, priority);
    }
    catch(ErrorException &ex) {
        cout<<"Priority must be a real number or integer."<<endl;
    }
}
