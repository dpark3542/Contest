#include "segtree.h"


template<typename T>
segtree<T>::segtree(int n):n(n) {
  tree = std::vector<T>(2 * n);
}

template<typename T>
void segtree<T>::build(std::vector<T> a) {
  for (int i = 0; i < n; i++) {
    tree[n + i] = a[i];
  }
  for (int i = n - 1; i > 0; i--) {
    tree[i] = tree[2 * i] + tree[2 * i + 1];
  }
}

template<typename T>
void segtree<T>::build(const T *a) {
  for (int i = 0; i < n; i++) {
    tree[n + i] = a[i];
  }
  for (int i = n - 1; i > 0; i--) {
    tree[i] = tree[2 * i] + tree[2 * i + 1];
  }
}

template<typename T>
T segtree<T>::operator[](int i) {
  return tree[n + i];
}

template<typename T>
void segtree<T>::update(int i, T x) {
  i += n;
  tree[i] = x;
  while (i > 1) {
    tree[i / 2] = tree[i] + tree[i ^ 1];
    i /= 2;
  }
}

template<typename T>
T segtree<T>::sum(int l, int r) {
  T res = 0;
  l += n;
  r += n + 1;
  while (l < r) {
    if (l & 1) {
      res += tree[l++];
    }
    if (r & 1) {
      res += tree[--r];
    }
    l /= 2;
    r /= 2;
  }
  return res;
}