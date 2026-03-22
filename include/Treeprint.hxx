#ifndef TREEPRINT_HXX
#define TREEPRINT_HXX

#ifdef TREEPRINT_TESTING
  #define TREEPRINT_FRIEND_TESTS
#else
  #define TREEPRINT_FRIEND_TESTS
#endif

#include <vector>

template<typename T>
struct Treenode
{
  T value_{};
  std::vector<Treenode*> children_{};

  Treenode(const T& val)
    : value_{val}
  {}
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
  bool init(Treenode<T>* head)
  {
    mHead = head;
    return true;
  }
  bool is_printable() const
  {
    return mIsPrintable;
  }

private:
  bool mIsPrintable{true};
  Treenode<T>* mHead{nullptr};

private:
  TREEPRINT_FRIEND_TESTS
};

#endif

