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
{};

class Treeprint
{
public:
  Treeprint() = default;
  Treeprint(const Treeprint&) = delete;
  Treeprint& operator=(const Treeprint&) = delete;
  Treeprint(Treeprint&&) = delete;
  Treeprint& operator=(Treeprint&&) = delete;
  template<typename T>
    requires std::derived_from<T, Treenode>
  bool init(T* root)
  {
    mRoot = root;
    return (root != nullptr);
  }

private:
  Treenode* mRoot{nullptr};

private:
  TREEPRINT_FRIEND_TESTS
};

#endif

