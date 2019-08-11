//
//  Automaton.h
//  Lab3CellularAutomata
//
//  Created by Margaret Peterson on 7/11/19.
//  Copyright © 2019 Margaret Peterson. All rights reserved.
//

#ifndef Automaton_h
#define Automaton_h

// ZyLab - Bitwise ops - 1D Cellular Automata
// Original - Prof. Loceff, Updates, Edits, Annotations: &
//

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

// This is a 1D automaton in which each child has three parent bits
// (8 possibilities). The rule can be any 8-bit number (0-255), in which
// each bit position n holds the value of the child whose parents have values
// given by the 3 bits of the binary rep of n.
//
// For extra credit, you can discuss in the forums how you might generalize
// this class to be agnostic to the number of bits in the parent (aka
// number of parents).

class Automaton {
private:
   bool rules[8];
   vector<int> thisGen;
   int extremeBit;    // implied everywhere "outside the interesting region"
   int displayWidth = DEFAULT_DISPLAY_WIDTH;  // an odd number so it can be perfectly centered

public:
   static const int MAX_DISPLAY_WIDTH = 121;
   static const int DEFAULT_DISPLAY_WIDTH = 79;
   static const int MIN_RULE = 0;
   static const int MAX_RULE = 255; // 2^(2^n)-1 where n = num parents.

   Automaton(int rule); 

   bool setRule(int rule);
   bool setDisplayWidth(int width);

   void resetToFirstGen();
   void propagateNewGen();

   string toStringCurrentGen(char charFor0, char charFor1) const;
};

#endif /* Automaton_h */
