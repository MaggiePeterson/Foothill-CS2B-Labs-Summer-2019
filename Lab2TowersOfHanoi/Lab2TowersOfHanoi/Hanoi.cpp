//
//  Hanoi.cpp
//  Lab2TowersOfHanoi
//
//  Created by Margaret Peterson on 7/11/19.
//  Copyright © 2019 Margaret Peterson. All rights reserved.
//

#include <sstream>

#include "Hanoi.h"

using namespace std;

// TODO: Define any private helper functions you need
/* Type your code here */

// Solve the N pole, M disc Towers of Hanoi problem and return a sequence of
// moves as a string in the form:
//  # Below, A->B means 'move the top disc on pole A to pole B'
//  1->2
//  1->3
//  2->3
//  ...
// solve() always means move all discs from pole 1 to pole 2 using 3 as a temp.

void Hanoi::recursive_solve(int discs, int start, int end, int aux) {

   if(discs< 1)
      return;

   if (discs == 1)
   {
      output += to_string(start) + "->" + to_string(end) + "\n";
      return;
   }
   recursive_solve(discs - 1, start, aux, end);
   output += to_string(start) + "->" + to_string(end) + "\n";
   recursive_solve(discs - 1, aux, end, start);

}

string Hanoi::solve()  {
   static int pole1 = 1, pole2 = 2, pole3 = 3;
   output = "# Below, A->B means 'move the top disc on pole A to pole B'\n";

   recursive_solve(nDiscs, pole1, pole2, pole3);
   return output;
}

