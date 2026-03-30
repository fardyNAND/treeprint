#include <gtest/gtest.h>

#define TREEPRINT_TESTING
#include "Treeprint.hxx"

struct Node : public Treenode
{
  int val{};
  Node(int x)
    : val{x}
  {}
};

TEST(TreeprintTest, NodeClear)
{
  Node* n1{new Node{11}};
  Node* n2{new Node{22}};
  Node* n3{new Node{33}};
  Node* n4{new Node{44}};
  Node* n5{new Node{55}};
  Node* n6{new Node{66}};
  Node* n7{new Node{77}};
  Node* n8{new Node{88}};

  n4->adopt(n5);
  n2->adopt(n3, n4);
  n1->adopt(n2);
  n5->adopt(n6);
  n6->adopt(n7);
  n7->adopt(n8);

  n1->clear();
  EXPECT_EQ(n1->get_children().size(), 0);

  delete n1;
  delete n2;
  delete n3;
  delete n4;
  delete n5;
  delete n6;
  delete n7;
  delete n8;
}

