//
//  main.cpp
//  Hanoi - Solve the N disc Towers of Hanoi problem
//
//  Created by Anand Venkataraman on 12/26/18.
//  Copyright © 2018 Anand Venkataraman. All rights reserved.
//
#include <iostream>

#include "Hanoi.h"

using namespace std;

int main(int argc, const char * argv[]) {
   int numDiscs = 4;

   Hanoi puzzle(numDiscs);
   string sol = puzzle.solve();
   cout <<sol <<endl;

   /* TODO: Make sure you run more tests here to cover corner cases.
    * Your program should be able to solve the puzzle with up to 10 discs.
    */

   return 0;
}
