//
//  Hanoi.h
//  Lab2TowersOfHanoi
//
//  Created by Margaret Peterson on 7/11/19.
//  Copyright © 2019 Margaret Peterson. All rights reserved.
//


#ifndef Hanoi_hpp
#define Hanoi_hpp

#include <iostream>
#include <sstream>

class Hanoi {
private:
   int nPoles;
   int nDiscs;
   std::string output;
   void recursive_solve(int discs, int pole1, int pole3, int pole2) ;

   // TODO
   /* Type your code here. Include any helper functions you need for solve() below */

public:
   Hanoi(int nd = 5): nDiscs(nd) { nPoles = 3; }  // Discuss > 4 poles cases in the forums

   // Returns a string with lines of the form "p->q" where p is the source pole number and
   // q the destination for each move. Consider each pole to have an ordinal label (1, 2 or 3).
   std::string solve() ;

};

#endif /* Hanoi_hpp */
