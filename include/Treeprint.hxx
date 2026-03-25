#ifndef TREEPRINT_HXX
#define TREEPRINT_HXX

#ifdef TREEPRINT_TESTING
  #define TREEPRINT_FRIEND_TESTS \
    FRIEND_TEST(TreeprintTest, NodeClear);
#else
  #define TREEPRINT_FRIEND_TESTS
#endif

#include <string>
#include <vector>

#define NAMEOF(x);

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
  void clear()
  {
    children_.clear();
  }

private:
  std::vector<Treenode<T>*> children_{};
};

struct Cell
{};

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

private:
  Treenode<T>* mRoot{nullptr};

private:
  TREEPRINT_FRIEND_TESTS
};

#endif

