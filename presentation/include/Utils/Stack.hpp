#include <list>

template <typename T>
class stack {
public:
  void push(const T& value) { elems.push_back(value); }
  void push(T&& value) { elems.push_back(std::move(value)); }
  void pop() { elems.pop_back(); }
  unsigned size() { return elems.size(); }
  T& top() { return elems.back(); }

private:
  std::list<T> elems;
};
