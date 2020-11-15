#ifndef CONTEST_SEGTREE_H
#define CONTEST_SEGTREE_H

#include <iostream>
#include <vector>

template<typename T>
class segtree {
private:
  int n;
  std::vector<T> tree;

public:
  explicit segtree(int n);
  void build(std::vector<T> const &a);
  void build(T const *a);
  T operator[](int i);
  void update(int i, T x);
  T sum(int a, int b);
};


#endif //CONTEST_SEGTREE_H
