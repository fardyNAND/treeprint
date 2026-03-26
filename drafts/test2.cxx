#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>


struct Treenode
{
  int val{};
  std::vector<Treenode *> children;

  Treenode(int n) : val(n) {};
};

struct Cell
{
  std::string val{};
  bool changed{false};

  Cell(std::string s, bool c) : val(s), changed(c) {};
};


std::unordered_set<size_t> used_row;

void modifyGrid(size_t row, size_t col, Treenode *root, std::vector<std::vector<Cell>> &grid, std::unordered_set<Treenode *> &visited)
{
  //when the node is null
  if (root == nullptr)
  {
    return;
  }

  //create new row in the grid of specific size
  std::vector<Cell> vec{col + 1, Cell{"", false}};
  grid.push_back(vec);

  //insert val in the Cell
  if (visited.find(root) != visited.end())//put cross instead of the val of the node if the node is already visited
  {
    grid[row][col].val = "❌️";
  }
  else //if not visited, insert val
  {
    grid[row][col].val = std::to_string(root->val);
  }
  grid[row][col].changed = true;
  used_row.insert(row);

  //connector
  if (col > 1)
  {
    grid[row][col-1].val = "─";
    grid[row][col-1].changed = true;
  }

  //draw straight upward line
  size_t i = row - 1;
  if(col >= 2)
  {

    grid[row][col - 2].val = "├─";
    grid[row][col - 2].changed = true;
    while (i > 0 and !grid[i][col - 2].changed)
    {
      grid[i][col - 2].val = "│";
      grid[i][col - 2].changed = true;
      --i;
    }
  }

  //get the next available coordinate
  size_t next_row = row + 1;
  size_t next_col = col + 2; //keep next col(col + 1) for a horizontal line


  while (used_row.find(next_row) != used_row.end())
  {
    ++next_row;
  }

  
  //prepare next generation
  std::vector<Treenode *> childs{root->children};
  //but if, the parent ia already visited, ignore the children
  if (visited.find(root) != visited.end())
  {
    childs.clear();
  }
  visited.insert(root);

  //recursion
  for (Treenode *child : childs)
  {
    modifyGrid(next_row, next_col, child, grid, visited);
    while (used_row.find(next_row) != used_row.end())
    {
      ++next_row;
    }
  }
}


void lineChng(std::vector<std::vector<Cell>> &grid)
{
  for (size_t i{}; i < grid.size(); ++i)
  {
    for (size_t j{}; j < grid[i].size(); ++j)
    {
      bool T_L{false}; 
      if (grid[i][j].val == "├─")
      {

        if ((i + 1) >= grid.size())
        {
          T_L = true;
        }
        else if (j >= (grid[i + 1].size() - 1))
        {
          T_L = true;
        }
        else if (grid[i + 1][j].val != "│" and grid[i + 1][j].val != "├─")
        {
          T_L = true;
        }
      }

      if (T_L)
      {
        grid[i][j].val = "└─";
      }
    }
  }
}

void showTree(Treenode *root)
{
  std::vector<std::vector<Cell>> grid;

  std::unordered_set<Treenode *> visited;
  modifyGrid(0, 0, root, grid, visited);
  lineChng(grid);

  for (auto v : grid)
  {
    for (auto n : v)
    {
      if (n.val == "")
      {
        std::cout << "  ";
      }
      else
      {
        std::cout << n.val;
      }
    }
    std::cout << "\n";
  }
}



int main()
{
  Treenode *node1 = new Treenode(1);
  Treenode *node2 = new Treenode(2);
  Treenode *node3 = new Treenode(3);
  Treenode *node4 = new Treenode(4);
  Treenode *node5 = new Treenode(5);
  Treenode *node6 = new Treenode(6);
  Treenode *node7 = new Treenode(7);
  Treenode *node8 = new Treenode(8);
  Treenode *node9 = new Treenode(9);
  Treenode *node10 = new Treenode(10);
  Treenode *node11 = new Treenode(11);
  Treenode *node12 = new Treenode(12);
  Treenode *node13 = new Treenode(13);
  Treenode *node14 = new Treenode(14);
  Treenode *node15 = new Treenode(15);
  Treenode *node16 = new Treenode(16);
  Treenode *node17 = new Treenode(17);
  Treenode *node18 = new Treenode(18);
  Treenode *node19 = new Treenode(19);
  Treenode *node20 = new Treenode(20);
  Treenode *node21 = new Treenode(21);
  Treenode *node22 = new Treenode(22);
  Treenode *node23 = new Treenode(23);
  Treenode *node24 = new Treenode(24);
  Treenode *node25 = new Treenode(25);
  Treenode *node26 = new Treenode(26);
  Treenode *node27 = new Treenode(27);
  Treenode *node28 = new Treenode(28);
  Treenode *node29 = new Treenode(29);
  Treenode *node30 = new Treenode(30);

  node1->children = {node2, node3, node20};

  node2->children = {node4, node5};

  node4->children = {node6, node7};

  node5->children = {node8, node9, node25, node19};

  node7->children = {node10, node11};

  node10->children = {node12, node13};

  node10->children = {node12};
  node12->children = {node13};
  node13->children = {node14};

  node20->children = {node15, node16, node17};
  node16->children = {node18, node19, node21};

  node8->children = {node25};

  // node1->children = {node2};
  // node2->children = {node3};
  // node3->children = {node4};
  // node4->children = {node5};
  // node5->children = {node6};
  // node6->children = {node7};
  // node7->children = {node8};
  // node8->children = {node9};
  // node9->children = {node10};
  // node10->children = {node11};
  // node11->children = {node12};
  // node12->children = {node13};
  // node13->children = {node14};
  // node14->children = {node15};
  // node15->children = {node16};
  // node16->children = {node17};
  // node17->children = {node18, node30};
  // node18->children = {node19};
  // node19->children = {node20};
  // node20->children = {node21};
  // node21->children = {node22};
  // node22->children = {node23};
  // node23->children = {node24};
  // node24->children = {node25};
  // node25->children = {node26};
  // node26->children = {node27};
  // node27->children = {node28};
  // node28->children = {node29};
  // node29->children = {node30};
  //
  //
  showTree(node1);

}
