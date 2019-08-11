// ZyLab - Bitwise ops - 1D Cellular Automata
// Original - Loceff, Updates, Edits, Annotations: &
//
// This main method is for your benefit. It will not be tested. But if you use it as
// an example to run your own tests, the likelihood of your Automaton code passing
// my tests may be higher.
// - &

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

#include "Automaton.h"

// getRows will rewind aut and return its first n generations as a string
// in which successive generations are separated by "\n". Within the strings
// 1 is represented by * and 0 by space.
string getRows(Automaton& aut, int n) {
   char charFor0 = '.', charFor1 = '*';
   stringstream ss;

   aut.resetToFirstGen();  // rewind

   while (--n >= 0) {
      ss << aut.toStringCurrentGen(charFor0, charFor1) << "\n";
      aut.propagateNewGen();
   }
   return ss.str();
}

int main()
{
   int rule;
   string userInput;

   while(1){
      cout << "Enter Rule (" << Automaton::MIN_RULE << " - " << Automaton::MAX_RULE << "): ";
      getline(cin, userInput);
      istringstream(userInput) >> rule;

      if (rule < Automaton::MIN_RULE || rule > Automaton::MAX_RULE) {
         cerr << "Sorry. That was an invalid rule number." <<endl;
         exit(1);
      }

      // Make the automaton and print its first 100 rows on cout
      Automaton aut(rule);
      aut.setDisplayWidth(101);
     cout << getRows(aut, 5) << endl;
      cout<<endl;
   }

   // TODO - run other tests to cover corner cases, limit checking, etc.
   /* Type your code here */
}
