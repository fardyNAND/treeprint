#ifndef TREEPRINT_HXX
#define TREEPRINT_HXX

#ifdef TREEPRINT_TESTING
  #define TREEPRINT_FRIEND_TESTS
#else
  #define TREEPRINT_FRIEND_TESTS
#endif

#include <algorithm>
#include <unordered_set>
#include <vector>

template<typename T>
struct Treenode
{
public:
  void adopt(const std::vector<Treenode*>& children)
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
  bool mIsPrintable{true};
  Treenode<T>* mRoot{nullptr};
  std::unordered_set<Treenode<T>*> mVisited{};

private:
  TREEPRINT_FRIEND_TESTS
};

#endif

