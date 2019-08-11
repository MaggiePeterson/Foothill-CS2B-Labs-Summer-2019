//
//  Automaton.cpp
//  Lab3CellularAutomata
//
//  Created by Margaret Peterson on 7/11/19.
//  Copyright © 2019 Margaret Peterson. All rights reserved.
//

#include <stdio.h>
#include "Automaton.h"

Automaton::Automaton(int rule){
   extremeBit = 0;
   setRule(rule);
   thisGen.push_back(1);
}

bool Automaton::setRule(int rule){

   if(rule > MAX_RULE || rule < MIN_RULE)
      return false;

   fill_n(rules, 8, 0); //set all to zero

   int i = 0;
   while (rule > 0) {

      rules[i] = rule % 2;
      rule /= 2;
      i++;
   }

/*  for(int i = 0; i< 8; i++){
      cout<<rules[i]<<" ";
   }
   cout<<endl;  */

   return true;

}

bool Automaton::setDisplayWidth(int width){

   if((width > MAX_DISPLAY_WIDTH) || !(width%2) || (width<0) ){ //larger than max, even, or negative
      displayWidth = DEFAULT_DISPLAY_WIDTH;
      return false;
   }

   this->displayWidth = width;
   return true;
}

void Automaton::resetToFirstGen(){
   thisGen.clear();
   thisGen.push_back(1);
   extremeBit = 0;
}

void Automaton::propagateNewGen(){

   vector<int>nextGen;

   //add 2 characters to each side
   thisGen.insert(thisGen.begin(), extremeBit);
   thisGen.insert(thisGen.begin(), extremeBit);
   thisGen.push_back(extremeBit);
   thisGen.push_back(extremeBit);

   //apply rule to thisGen
   for(int i = 1; i < thisGen.size()-1; i++){ //do all except the filler elements
      //bit shift then combine to form binary number
      nextGen.push_back(rules[(thisGen[i - 1] << 2) | (thisGen[i] << 1) | (thisGen[i + 1])]);
   }

   thisGen = nextGen;
   extremeBit = rules[extremeBit << 2 | extremeBit << 1 | extremeBit << 0]; //update extremeBit

}

string Automaton::toStringCurrentGen(char charFor0, char charFor1) const{

   string gen;
   vector<int>thisGen = this->thisGen;

   //make correct length
   if(thisGen.size() < displayWidth){ //add padding extremeBit

      while(thisGen.size() < displayWidth){
         thisGen.insert(thisGen.begin(), extremeBit);
         thisGen.push_back(extremeBit);
      }
   }
   else if (thisGen.size() > displayWidth){ //remove from both sides

      while(thisGen.size() > displayWidth){
         thisGen.erase(thisGen.begin());
         thisGen.erase(thisGen.end()-1);
      }
   }

   //put vector into string
   for(int i = 0; i < thisGen.size(); i++){
      if(thisGen[i])
         gen += charFor1;
      else
         gen += charFor0;
   }

   return gen;
   
}
