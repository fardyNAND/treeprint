#include <algorithm>
#include <iostream>
#include <unordered_set>
#include <vector>

struct Treenode
{
    int val{};
    std::vector<Treenode *> children;

    Treenode(int n) : val(n){};
};

struct Cell
{
    std::string val{};
    bool changed{false};

    Cell(std::string n, bool c) : val(n), changed(c){};
};

//get total amount of nodes
size_t totalNodes(Treenode *root, std::unordered_set<Treenode*> &visited)
{
    if (root == nullptr or visited.find(root) != visited.end())
    {
        return 0;
    }
    else
    {
      visited.insert(root);
    }

    size_t count = 1;
    for (Treenode *child : root->children)
    {
        count += totalNodes(child, visited);
    }

    return count;
}
//get the maximum depth of the tree
size_t maxDepth(Treenode *root, std::unordered_set<Treenode*> &visited)
{
    if (root == nullptr or visited.find(root) != visited.end())
    {
        return 0;
    }
    else
    {
      visited.insert(root);
    }

    size_t depth = 0;
    for (Treenode *child : root->children)
    {
        depth = std::max(depth, maxDepth(child, visited));
    }
    return 1 + depth;
}

//store the used row and use it to avoid collision
std::unordered_set<size_t> used_row;

void modifyGrid(size_t row, size_t col, size_t amount, Treenode *root, std::vector<std::vector<Cell>> &grid, std::unordered_set<Treenode*> &visited)
{
    if (root == nullptr or visited.find(root) != visited.end())
    {
        return;
    }
    else
    {
      visited.insert(root);
    }

    grid[row][col].val = std::to_string(root->val);
    grid[row][col].changed = true;
    used_row.insert(row);

    //connector
    if (col >= 1)
    {
        grid[row][col - 1].val = "─";
        grid[row][col - 1].changed = true;
    }

    size_t i = row - 1;
    if (col >= 2)
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
    size_t next_col = col + 2;

    while (next_row < amount and used_row.find(next_row) != used_row.end())
    {
        ++next_row;
    }
    
    
    for (Treenode *child : root->children)
    {
        modifyGrid(next_row, next_col, amount, child, grid, visited);
        while (next_row < amount and used_row.find(next_row) != used_row.end())
        {
            ++next_row;
        }
    }
}

void lineChng(std::vector<std::vector<Cell>> &grid)
{
    size_t row = grid.size();
    size_t col = grid[0].size();
    for (size_t i{}; i < (row - 1); ++i)
    {
        for (size_t j{}; j < col; ++j)
        {
            if (grid[i][j].val == "├─" and grid[i + 1][j].val != "│" and grid[i + 1][j].val != "├─")
            {
                grid[i][j].val = "└─";
            }
        }
    }
}

void showTree(Treenode *root)
{
    std::unordered_set<Treenode*> visited;
    size_t amount = totalNodes(root, visited);
    visited.clear();
    size_t depth = maxDepth(root, visited);
    visited.clear();

    std::vector<std::vector<Cell>> grid(amount + 2, std::vector<Cell>(2 * depth + 2, Cell("", false)));

    modifyGrid(0, 0, amount, root, grid, visited);
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
    node25->children = {node19};
    

    // node1->children = {node2};
    // node2->children = {node3};
    // node3->children = {node4};
    // node4->children = {node2};
    showTree(node1);
}
