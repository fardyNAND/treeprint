#ifndef TREEPRINT_HXX
#define TREEPRINT_HXX

#ifdef TREEPRINT_TESTING
#define TREEPRINT_FRIEND_TESTS \
  FRIEND_TEST(TreeprintTest, NodeClear);
#else
#define TREEPRINT_FRIEND_TESTS
#endif

#include <concepts>
#include <string>
#include <type_traits>
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

private:
  template <typename T>
  std::string emitString(T val)
  {
    if constexpr (std::same_as<std::decay_t<T>, std::string>)
      return val;
    else
      return std::to_string(val);
  }

private:
  Treenode* mRoot{nullptr};
  Tagtype Nodetype::* mPtr{nullptr};

private:
  TREEPRINT_FRIEND_TESTS
};

#endif

