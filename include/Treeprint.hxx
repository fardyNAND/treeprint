#ifndef TREEPRINT_HXX
#define TREEPRINT_HXX

#ifdef TREEPRINT_TESTING
#define TREEPRINT_FRIEND_TESTS \
  FRIEND_TEST(TreeprintTest, NodeClear);
#else
#define TREEPRINT_FRIEND_TESTS
#endif

#include <algorithm>
#include <concepts>
#include <cstddef>
#include <iostream>
#include <string>
#include <type_traits>
#include <unordered_set>
#include <vector>

struct Treenode
{
public:
  void adopt(const std::vector<Treenode*>& children)
  {
    children_ = children;
  }
  const std::vector<Treenode*>& get_children() const
  {
    return children_;
  }
  void clear()
  {
    children_.clear();
  }

private:
  std::vector<Treenode*> children_{};
};

struct Cell
{
  std::string val_{};
  bool changed_{false};
  Cell(const std::string& s, bool c)
    : val_{s},
      changed_{c} {};
};

template <typename T>
concept Stringable =
  std::convertible_to<T, std::string> or
  requires(T val) {
    {
      std::to_string(val)
    }
    -> std::convertible_to<std::string>;
  };

template <typename Nodetype, typename Tagtype>
  requires std::derived_from<Nodetype, Treenode> and
  Stringable<Tagtype>
class Treeprint
{
public:
  Treeprint() = default;
  Treeprint(const Treeprint&) = delete;
  Treeprint& operator=(const Treeprint&) = delete;
  Treeprint(Treeprint&&) = delete;
  Treeprint& operator=(Treeprint&&) = delete;

  template <typename T>
    requires std::derived_from<T, Treenode>
  bool init(T* root)
  {
    mRoot = root;
    return (root != nullptr);
  }

  void register_tag(Tagtype Nodetype::* ptr)
  {
    mPtr = ptr;
  }

  void print()
  {
    this->display();
  }

private:
  template <typename T>
  std::string emitString(T val)
  {
    if constexpr (std::same_as<std::decay_t<T>, std::string>)
      return val;
    else
      return std::to_string(val);
  }

  void modifyGrid(size_t row, size_t col, Treenode* root)
  {
    if (root == nullptr)
      return;

    std::vector<Cell> vec{col + 1, Cell{"", false}};
    mGrid.push_back(vec);

    if (mVisited.find(root) != mVisited.end())
      mGrid[row][col].val_ = "❌️";
    else
      mGrid[row][col].val_ = this->emitString(static_cast<Nodetype*>(root)->*mPtr);
    mGrid[row][col].changed_ = true;
    mUsedRow.insert(row);

    if (col > 1)
    {
      mGrid[row][col - 1].val_ = "─";
      mGrid[row][col - 1].changed_ = true;
    }

    size_t i{row - 1};
    if (col >= 2)
    {
      mGrid[row][col - 2].val_ = "├─";
      mGrid[row][col - 2].changed_ = true;
      while (i > 0 and !mGrid[i][col - 2].changed_)
      {
        mGrid[i][col - 2].val_ = "│";
        mGrid[i][col - 2].changed_ = true;
        --i;
      }
    }

    size_t next_row{row + 1};
    size_t next_col{col + 2};

    while (mUsedRow.find(next_row) != mUsedRow.end())
    {
      ++next_row;
    }

    std::vector<Treenode*> children{root->get_children()};
    if (mVisited.find(root) != mVisited.end())
    {
      children.clear();
    }
    mVisited.insert(root);

    for (Treenode* child : children)
    {
      modifyGrid(next_row, next_col, child);
      while (mUsedRow.find(next_row) != mUsedRow.end())
      {
        ++next_row;
      }
    }
  }

  void modifyLine()
  {
    for (size_t i{}; i < mGrid.size(); ++i)
    {
      for (size_t j{}; j < mGrid[i].size(); ++j)
      {
        bool T_L{false};
        if (mGrid[i][j].val_ == "├─")
        {

          if ((i + 1) >= mGrid.size())
            T_L = true;
          else if (j >= (mGrid[i + 1].size() - 1))
            T_L = true;
          else if (mGrid[i + 1][j].val_ != "│" and mGrid[i + 1][j].val_ != "├─")
            T_L = true;
        }

        if (T_L)
          mGrid[i][j].val_ = "└─";
      }
    }
  }

  void display()
  {
    this->modifyGrid(0, 0, mRoot);
    this->modifyLine();
    for (auto v : mGrid)
    {
      for (auto n : v)
      {
        if (n.val_ == "")
          std::cout << "  ";
        else
          std::cout << n.val_;
      }
      std::cout << std::endl;
    }
  }

private:
  Treenode* mRoot{nullptr};
  Tagtype Nodetype::* mPtr{nullptr};
  std::vector<std::vector<Cell>> mGrid{};
  std::unordered_set<Treenode*> mVisited{};
  std::unordered_set<size_t> mUsedRow{};

private:
  TREEPRINT_FRIEND_TESTS
};

#endif

