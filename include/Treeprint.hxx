#ifndef TREEPRINT_HXX
#define TREEPRINT_HXX

#ifdef TREEPRINT_TESTING
  #define TREEPRINT_FRIEND_TESTS \
    FRIEND_TEST(TreeprintTest, NodeNumber);
#else
  #define TREEPRINT_FRIEND_TESTS
#endif

#include <algorithm>
#include <cassert>
#include <exception>
#include <stack>
#include <stdexcept>
#include <unordered_set>
#include <vector>

template<typename T>
struct Treenode
{
public:
  void adopt(const std::vector<Treenode<T>*>& children)
  {
    children_ = children;
  }
  const std::vector<Treenode<T>*>& get_children() const
  {
    return children_;
  }

private:
  std::vector<Treenode<T>*> children_{};
};

template<typename T>
struct Cell
{
};

template<typename T>
class Treeprint
{
public:
  Treeprint() = default;
  bool init(Treenode<T>* root)
  {
    mRoot = root;
    return (root != nullptr);
  }
  bool is_printable() const
  {
    return mIsPrintable;
  }

private:
  size_t getTotalNodes(Treenode<T>* root)
  {
    mVisited.clear();
    if (root == nullptr)
      return 0;

    std::stack<Treenode<T>*> stack{};
    stack.push(root);
    size_t count{};

    while (stack.empty() == false)
    {
      Treenode<T>* current{stack.top()};
      stack.pop();
      ++count;

      if (mVisited.find(current) != mVisited.end())
      {
        return 0;
      }
      else mVisited.insert(current);

      for (Treenode<T>* node : current->get_children())
      {
        if (node != nullptr)
          stack.push(node);
      }
    }

    return count;
  }

private:
  bool mIsPrintable{true};
  Treenode<T>* mRoot{nullptr};
  std::unordered_set<Treenode<T>*> mVisited{};

private:
  TREEPRINT_FRIEND_TESTS
};

#endif

