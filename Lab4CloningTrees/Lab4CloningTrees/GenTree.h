//
//  GenTree.h
//  Lab4CloningTrees
//
//  Created by Margaret Peterson on 7/16/19.
//  Copyright © 2019 Margaret Peterson. All rights reserved.
//

#ifndef GenTree_h
#define GenTree_h

#include <iostream>

class GenTree {
public:
   class Node;

private:
   Node *root;

public:
   GenTree(Node *p = nullptr) : root(p) {}
   GenTree(const GenTree& that) { *this = that; }
   GenTree& operator=(const GenTree& that); // Deep clone

   Node *getRoot() { return root; }
   Node *setRoot(Node *p) { return root = p; }
   std::string toString() const;
   bool deleteNodes();

   // The == operator returns true if the two trees are structurally
   // identical. But actual node pointers may be different.
   bool operator==(const GenTree& that) const;
   bool operator!=(const GenTree& that) const { return !(*this == that); }
   friend std::ostream& operator<<(std::ostream& os, const GenTree& tree) {
      return os << tree.toString();
   };

   // inner class
   class Node {
   private:
      std::string data;
      Node *sibling, *child;

   public:
      Node(std::string s = "") : data(s), sibling(nullptr), child(nullptr) {}
      Node(const Node& that);
      const Node& operator=(const Node& that); // Deep clone
      ~Node();

      void setData(std::string s) { data = s; }
      void setSibling(Node *p) { sibling = p; }
      void setChild(Node *p) { child = p; }
      std::string getData() const { return data; }
      Node *getSibling() const { return sibling; }
      Node *getChild() const { return child; }

      bool operator==(const Node& that) const;
      bool operator!=(const Node& that) const { return !(*this == that); }
   };
};


#endif /* GenTree_h */
