/*
 * File: KarelGoesHome.cpp
 * -----------------------
 * Starter file for the KarelGoesHome problem.
 */

#include <iostream>
#include <iomanip>
#include "error.h"
using namespace std;

/* Function prototypes */

int countPaths(int street, int avenue);

/* Main program */

int main() {
   cout<<countPaths(2, 3)<<endl;
   return 0;
}

/*
 * Function: countPaths
 * Usage: int nPaths = countPaths(street, avenue);
 * -----------------------------------------------
 * Counts the paths from a particular street/avenue position in
 * Karel's world to the origin, subject to the restriction that
 * Karel can move only west and south.
 */

int countPaths(int street, int avenue) {
   if(street < 1 || avenue < 1) {
       error("ARGUMENTS MUST BE GREATER THAN 1!");
   }
   if(street == 1 && avenue == 1) {
       return 1;
   }
   if(street > 1 && avenue > 1) {
       return countPaths(street - 1, avenue) + countPaths(street, avenue - 1);
   }
   if(street > 1) {
       return countPaths(street - 1, avenue);
   }
   return countPaths(street, avenue - 1);
}
