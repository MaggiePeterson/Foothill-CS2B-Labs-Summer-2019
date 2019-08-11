//
//  main.cpp
//  GenTree
//
//  Created by Anand Venkataraman on 12/24/18.
//  Copyright © 2018 Anand Venkataraman. All rights reserved.
//
//  Complete the TODO items. This, by itself, doesn't score points. But
//  it increases the likelihood that my unit tests on your class code
//  pass. Those are worth actual points.
//
//  I would be happy if you follow a similar coding style as mine. It's easier
//  for me to read your code that way.

#include <iostream>
#include <vector>

using namespace std;

#include "GenTree.h"

// A fun little function we wrote in CS2A. Generates a cool sounding
// name. We will use this in main()
string makeName(int len) {
   string name = "";
   const string vowels = "aeiouy";
   const string consonants = "bcdfghjklmnpqrstvwxz";
   bool lastLetterWasVowel = rand() > RAND_MAX/2;

   for (int i = 0; i < len; i++) {
      name += lastLetterWasVowel ?
      consonants[rand() % consonants.length()] :
      vowels[rand() % vowels.length()];
      lastLetterWasVowel = !lastLetterWasVowel;
   }
   return name;
}

int main(int argc, const char * argv[]) {
   GenTree tree;
   int nameLen = 5;

   srand((unsigned) time(NULL));

   GenTree::Node *root = new GenTree::Node("root");
   tree.setRoot(root);

   // Push 3 children
   GenTree::Node *p1 = new GenTree::Node(makeName(nameLen));
   root->setChild(p1);
   GenTree::Node *p2 = new GenTree::Node(makeName(nameLen));
   p1->setSibling(p2);
   GenTree::Node *p3 = new GenTree::Node(makeName(nameLen));
   p2->setSibling(p3);

   GenTree::Node *p11 = new GenTree::Node(makeName(nameLen));
   p1->setChild(p11);
   GenTree::Node *p12 = new GenTree::Node(makeName(nameLen));
   p11->setSibling(p12);

   GenTree::Node *p21 = new GenTree::Node(makeName(nameLen));
   p2->setChild(p21);
   GenTree::Node *p22 = new GenTree::Node(makeName(nameLen));
   p21->setSibling(p22);
   GenTree::Node *p23 = new GenTree::Node(makeName(nameLen));
   p22->setSibling(p23);

   GenTree::Node *p31 = new GenTree::Node(makeName(nameLen));
   p3->setChild(p31);
   GenTree::Node *p32 = new GenTree::Node(makeName(nameLen));
   p31->setSibling(p32);

   // Prelim test for assignment operator
   GenTree copy = tree;
   cout <<"Orig:\n" << tree <<endl;
   cout <<"Copy:\n" << copy <<endl;

   // TODO: Additional tests here to make sure that
   // though the trees are equal, they are not identical
   // E.g. They contain distinct pointers at corresponding positions.

   // Test the comparison operator
   if (tree == copy) {
      cout << "They are equal" <<endl;
   } else {
      cout << "They are not equal" <<endl;
   }

   // TODO: Also test to make sure that if you change values in one
   // tree, it doesn't change in the other tree. E.g.

   // Clean up. Since main created, main must also destroy.
   // GenTree *must not* destroy.
   tree.deleteNodes();
   copy.deleteNodes();

   return 0;
}
