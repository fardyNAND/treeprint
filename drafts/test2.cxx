#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>


namespace color
{
typedef std::string s;

inline s col(const std::string &x)
{
  return "\033[" + x + "m";
};

inline s res{col("0")};
inline s bol{col("1")};
inline s und{col("4")};
inline s bli{col("5")};
inline s inv{col("7")};

inline s fblack{col("30")};
inline s fred{col("31")};
inline s fgreen{col("32")};
inline s fyellow{col("33")};
inline s fblue{col("34")};
inline s fmagenta{col("35")};
inline s fcyan{col("36")};
inline s fwhite{col("37")};

inline s bblack{col("40")};
inline s bred{col("41")};
inline s bgreen{col("42")};
inline s byellow{col("43")};
inline s bblue{col("44")};
inline s bmagenta{col("45")};
inline s bcyan{col("46")};
inline s bwhite{col("47")};

} // namespace color



struct Treenode
{
  int val{};
  std::vector<Treenode *> children;

  Treenode(int n) : val(n) {};
};

struct Cell
{
  Treenode *address{nullptr};
  std::string val{};
  bool changed{false};
  std::string tone{};

  Cell(Treenode *a, std::string s, bool c) : address(a), val(s), changed(c) {};
  Cell(std::string s, bool c) : val(s), changed(c) {};
};


//std::unordered_set<size_t> used_row;

void modifyGrid(size_t row, size_t col, Treenode *root, std::vector<std::vector<Cell>> &grid, std::unordered_set<Treenode *> &visited, std::unordered_set<size_t> &usedRow)
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
    grid[row][col].address = root;
    grid[row][col].val = std::to_string(root->val);
  }
  grid[row][col].changed = true;
  usedRow.insert(row);

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


  while (usedRow.find(next_row) != usedRow.end())
  {
    ++next_row;
  }


  //prepare next generation
  std::vector<Treenode *> childs{root->children};
  //but if, the parent is already visited, ignore the children
  if (visited.find(root) != visited.end())
  {
    childs.clear();
  }
  visited.insert(root);

  //recursion
  for (Treenode *child : childs)
  {
    modifyGrid(next_row, next_col, child, grid, visited, usedRow);
    while (usedRow.find(next_row) != usedRow.end())
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

//draw a path from the root of the tree to the target node
void pathToRoot(std::vector<std::vector<Cell>> &grid, Treenode *target)
{
  for (size_t row{}; row < grid.size(); ++row)
  {
    size_t lastCol = grid[row].size() - 1;
    if (target == grid[row][lastCol].address)
    {
      grid[row][lastCol].tone = "green";
      if (lastCol >= 2)
      {
        lastCol -= 2;
      }
      while (lastCol >= 0)
      {
        while (row > 0 and (grid[row][lastCol].val == "│" or grid[row][lastCol].val == "└─" or grid[row][lastCol].val == "├─"))
        {
          grid[row][lastCol].tone = "red";
          grid[row][lastCol + 1].tone = "red";
          --row;
        }
        if (grid[row][lastCol].tone == "")
        {
          grid[row][lastCol].tone = "magenta";
        }

        if (lastCol < 2)
          break;
        lastCol -= 2;
      }
      break;
    }
  }
}



void printGrid(std::vector<std::vector<Cell>> &grid)
{

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
        if (n.tone == "")
        {
          std::cout <<n.val;
        }
        else if (n.tone == "red")
        {
          std::cout <<color::fred <<n.val <<color::res;
        }
        else if (n.tone == "green")
        {
          std::cout <<color::fgreen <<n.val <<color::res;
        }
        else if (n.tone == "cyan")
        {
          std::cout <<color::fcyan <<n.val <<color::res;
        }
        else if (n.tone == "blue")
        {
          std::cout <<color::fblue <<n.val <<color::res;
        }
        else if (n.tone == "magenta")
        {
          std::cout <<color::fmagenta <<n.val <<color::res;
        }
      }
    }
    std::cout << "\n";
  }
}



void showTree(Treenode *root, std::vector<Treenode *> targets)
{
  std::vector<std::vector<Cell>> grid;

  std::unordered_set<Treenode *> visited;
  std::unordered_set<size_t> usedRow;

  modifyGrid(0, 0, root, grid, visited, usedRow);
  lineChng(grid);

  //draw the paths from root to target nodes
  for (auto N : targets)
  {
    pathToRoot(grid, N);
  }

  printGrid(grid);
}

int main()
{
  // Treenode *node1 = new Treenode(1);
  // Treenode *node2 = new Treenode(2);
  // Treenode *node3 = new Treenode(3);
  // Treenode *node4 = new Treenode(4);
  // Treenode *node5 = new Treenode(5);
  // Treenode *node6 = new Treenode(6);
  // Treenode *node7 = new Treenode(7);
  // Treenode *node8 = new Treenode(8);
  // Treenode *node9 = new Treenode(9);
  // Treenode *node10 = new Treenode(10);
  // Treenode *node11 = new Treenode(11);
  // Treenode *node12 = new Treenode(12);
  // Treenode *node13 = new Treenode(13);
  // Treenode *node14 = new Treenode(14);
  // Treenode *node15 = new Treenode(15);
  // Treenode *node16 = new Treenode(16);
  // Treenode *node17 = new Treenode(17);
  // Treenode *node18 = new Treenode(18);
  // Treenode *node19 = new Treenode(19);
  // Treenode *node20 = new Treenode(20);
  // Treenode *node21 = new Treenode(21);
  // // Treenode *node22 = new Treenode(22);
  // // Treenode *node23 = new Treenode(23);
  // // Treenode *node24 = new Treenode(24);
  // Treenode *node25 = new Treenode(25);
  // // Treenode *node26 = new Treenode(26);
  // // Treenode *node27 = new Treenode(27);
  // // Treenode *node28 = new Treenode(28);
  // // Treenode *node29 = new Treenode(29);
  // Treenode *node30 = new Treenode(30);
  //
  // node1->children = {node2, node3, node20};
  //
  // node2->children = {node4, node5};
  //
  // node4->children = {node6, node7};
  //
  // node5->children = {node8, node9, node19};
  //
  // node7->children = {node10, node11};
  //
  // node10->children = {node12, node13};
  //
  // node10->children = {node12};
  // node12->children = {node13};
  // node13->children = {node14};
  //
  // node20->children = {node15, node16, node17};
  // node16->children = {node18, node30, node21};
  //
  // node8->children = {node25};


  // Create 60 nodes
  Treenode *n1 = new Treenode(1);
  Treenode *n2 = new Treenode(2);
  Treenode *n3 = new Treenode(3);
  Treenode *n4 = new Treenode(4);
  Treenode *n5 = new Treenode(5);
  Treenode *n6 = new Treenode(6);
  Treenode *n7 = new Treenode(7);
  Treenode *n8 = new Treenode(8);
  Treenode *n9 = new Treenode(9);
  Treenode *n10 = new Treenode(10);
  Treenode *n11 = new Treenode(11);
  Treenode *n12 = new Treenode(12);
  Treenode *n13 = new Treenode(13);
  Treenode *n14 = new Treenode(14);
  Treenode *n15 = new Treenode(15);
  Treenode *n16 = new Treenode(16);
  Treenode *n17 = new Treenode(17);
  Treenode *n18 = new Treenode(18);
  Treenode *n19 = new Treenode(19);
  Treenode *n20 = new Treenode(20);
  Treenode *n21 = new Treenode(21);
  Treenode *n22 = new Treenode(22);
  Treenode *n23 = new Treenode(23);
  Treenode *n24 = new Treenode(24);
  Treenode *n25 = new Treenode(25);
  Treenode *n26 = new Treenode(26);
  Treenode *n27 = new Treenode(27);
  Treenode *n28 = new Treenode(28);
  Treenode *n29 = new Treenode(29);
  Treenode *n30 = new Treenode(30);
  Treenode *n31 = new Treenode(31);
  Treenode *n32 = new Treenode(32);
  Treenode *n33 = new Treenode(33);
  Treenode *n34 = new Treenode(34);
  Treenode *n35 = new Treenode(35);
  Treenode *n36 = new Treenode(36);
  Treenode *n37 = new Treenode(37);
  Treenode *n38 = new Treenode(38);
  Treenode *n39 = new Treenode(39);
  Treenode *n40 = new Treenode(40);
  Treenode *n41 = new Treenode(41);
  Treenode *n42 = new Treenode(42);
  Treenode *n43 = new Treenode(43);
  Treenode *n44 = new Treenode(44);
  Treenode *n45 = new Treenode(45);
  Treenode *n46 = new Treenode(46);
  Treenode *n47 = new Treenode(47);
  Treenode *n48 = new Treenode(48);
  Treenode *n49 = new Treenode(49);
  Treenode *n50 = new Treenode(50);
  Treenode *n51 = new Treenode(51);
  Treenode *n52 = new Treenode(52);
  Treenode *n53 = new Treenode(53);
  Treenode *n54 = new Treenode(54);
  Treenode *n55 = new Treenode(55);
  Treenode *n56 = new Treenode(56);
  Treenode *n57 = new Treenode(57);
  Treenode *n58 = new Treenode(58);
  Treenode *n59 = new Treenode(59);
  Treenode *n60 = new Treenode(60);

  // Root spread
  n1->children = {n2, n3};

  // ===== ULTRA LONG LEFT CHAIN =====
  n2->children = {n6};
  n6->children = {n7};
  n7->children = {n8};
  n8->children = {n9};
  n9->children = {n10};
  n10->children = {n11};
  n11->children = {n12};
  n12->children = {n13};
  n13->children = {n14};

  // Explosion
  n14->children = {n15, n16, n17};

  n15->children = {n18};
  n18->children = {n19};
  n19->children = {n20};

  n16->children = {n21, n22};
  n21->children = {n23};
  n23->children = {n24};

  n22->children = {n25};

  showTree(n1, {n13, n11, n25, n21});

}
