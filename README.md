# Treeprint

Having a hard time visualizing trees in your head? Tired of using pen and paper? Fret not! `Treeprint` got your back! Print your trees in terminal with a single include cause `Treeprint` is header-only! All you need is a C++20 compiler.

# Usage

Include `Treeprint`.
```cpp
#include "Treeprint.hxx"
```

Define your struct however you want, just make sure it inherits from `Treenode`.
```cpp
struct Node : public Treenode
{
  int ival{};
  double dval{};
  std::string sval{};
  Node(int x, double y, std::string z)
    : ival{x}, dval{y}, sval{z}
  {}
};
```

Let's beg some memories for our nodes.
```cpp
  Node* n1{new Node{11, 11.11, "n1"}};
  Node* n2{new Node{22, 22.22, "n2"}};
  Node* n3{new Node{33, 33.33, "n3"}};
  Node* n4{new Node{44, 44.44, "n4"}};
  Node* n5{new Node{55, 55.55, "n5"}};
  Node* n6{new Node{66, 66.66, "n6"}};
  Node* n7{new Node{77, 77.77, "n7"}};
  Node* n8{new Node{88, 88.88, "n8"}};
```

Make our nodes foster some children.
```cpp
  n7->adopt(n8);
  n6->adopt(n7);
  n3->adopt(n5, n6);
  n2->adopt(n3, n4);
  n1->adopt(n2);
```

It's `Treeprint` time! `Treeprint` takes the shape `Treeprint<Node, T>` where Node is a struct/class inherited from `Treenode` and `T` is a data type convertible to `std::string`. `T` is the type of thing that you're going to print in terminal.
```cpp
Treeprint<Node, std::string> tp;  // This means the data member that you're going to print is a std::string belonging in Node. You can register whatever you want as long as they are convertible to std::string.
```

Initialize `Treeprint` with a root node.
```cpp
tp.init(n1);
```

Register your desired data member. Its data type must match with `T` as in `Treeprint<Node, T>`.
```cpp
tp.register_tag(&Node::sval);
```

Print!
```cpp
tp.print();
```

Output:
```
n1
└──n2
    ├──n3
    │  ├──n5
    │  └──n6
    │      └──n7
    │          └──n8
    └──n4
```

Your might get clever and do something like this:
```cpp
n7->adopt(n6, n5);
```

Fret not cause `Treeprint` is clever too! It actively detects and blocks any cycles.
```
n1
└──n2
    ├──n3
    │  ├──n5
    │  └──n6
    │      └──n7
    │          ├──n8
    │          ├──❌️
    │          └──❌️
    └──n4
```

Anyways, don't be a leaker if you begged memory the old way!
```cpp
delete n1;
delete n2;
delete n3;
delete n4;
delete n5;
delete n6;
delete n7;
delete n8;
```

# TODO

- A `trace()` method to pretty-trace any node anywhere in the tree.

# Author

Written from absolute scratch by two brothers.

# License

MIT

