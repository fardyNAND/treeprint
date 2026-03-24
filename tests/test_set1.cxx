#include "Treeprint.hxx"
#define TREEPRINT_TESTING

#include <gtest/gtest.h>

struct Node : public Treenode<int>
{
  int val{};
  Node(int x)
    : val{x}
  {}
};

int main()
{
  Node* n1{new Node{11}};
  Node* n2{new Node{22}};
  Node* n3{new Node{33}};
  Node* n4{new Node{44}};
  Node* n5{new Node{55}};
  n4->adopt({n5});
  n2->adopt({n3, n4});
  n1->adopt({n2});

  Treeprint<int> tp;
  tp.init(n1);
}

