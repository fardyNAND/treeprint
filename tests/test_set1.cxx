#include <gtest/gtest.h>

#define TREEPRINT_TESTING
#include "Treeprint.hxx"

struct Node : public Treenode<int>
{
  int val{};
  Node(int x)
    : val{x}
  {}
};

TEST(TreeprintTest, NodeNumber)
{
  Node* n1{new Node{11}};
  Node* n2{new Node{22}};
  Node* n3{new Node{33}};
  Node* n4{new Node{44}};
  Node* n5{new Node{55}};
  Node* n6{new Node{66}};
  Node* n7{new Node{77}};
  Node* n8{new Node{88}};

  n4->adopt({n5});
  n2->adopt({n3, n4});
  n1->adopt({n2});

  Treeprint<int> tp;
  tp.init(n1);
  EXPECT_EQ(tp.getTotalNodes(n1), 5);
  EXPECT_EQ(tp.getTotalNodes(n2), 4);
  EXPECT_EQ(tp.getTotalNodes(n3), 1);
  EXPECT_EQ(tp.getTotalNodes(n4), 2);
  EXPECT_EQ(tp.getTotalNodes(n5), 1);
  EXPECT_EQ(tp.getTotalNodes(nullptr), 0);

  n5->adopt({n6});
  n6->adopt({n7});
  n7->adopt({n8});
  EXPECT_EQ(tp.getTotalNodes(n5), 4);
  EXPECT_EQ(tp.getTotalNodes(n6), 3);
  EXPECT_EQ(tp.getTotalNodes(n7), 2);
  EXPECT_EQ(tp.getTotalNodes(n8), 1);

  delete n1;
  delete n2;
  delete n3;
  delete n4;
  delete n5;
  delete n6;
  delete n7;
  delete n8;
}

