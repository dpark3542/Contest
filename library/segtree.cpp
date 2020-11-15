#include "segtree.h"

#ifndef _GLIBCXX_DEBUG
#define _GLIBCXX_DEBUG false
#endif

template<typename T>
segtree<T>::segtree(int n):n(n) {
  if (_GLIBCXX_DEBUG) {
    if (n > std::vector<T>::max_size() / 2) {
      std::cerr << "Segtree of size " << n << " requested. Max size is " << std::vector<T>::max_size() / 2 << '.' << std::endl;
      return;
    }
  }
  tree = std::vector<T>(2 * n);
}

template<typename T>
void segtree<T>::build(std::vector<T> const &a) {
  for (int i = 0; i < n; i++) {
    tree[n + i] = a[i];
  }
  for (int i = n - 1; i > 0; i--) {
    tree[i] = tree[2 * i] + tree[2 * i + 1];
  }
}

template<typename T>
void segtree<T>::build(T const *a) {
  for (int i = 0; i < n; i++) {
    tree[n + i] = a[i];
  }
  for (int i = n - 1; i > 0; i--) {
    tree[i] = tree[2 * i] + tree[2 * i + 1];
  }
}

template<typename T>
T segtree<T>::operator[](int i) {
  if (_GLIBCXX_DEBUG) {
    if (i < 0 || i >= n) {
      std::cerr << "Segtree index " << i << " out of bounds." << std::endl;
      return;
    }
  }
  return tree[n + i];
}

template<typename T>
void segtree<T>::update(int i, T x) {
  if (_GLIBCXX_DEBUG) {
    if (i < 0 || i >= n) {
      std::cerr << "Segtree index " << i << " out of bounds." << std::endl;
      return;
    }
  }
  i += n;
  tree[i] = x;
  while (i > 1) {
    tree[i / 2] = tree[i] + tree[i ^ 1];
    i /= 2;
  }
}

template<typename T>
T segtree<T>::sum(int l, int r) {
  if (_GLIBCXX_DEBUG) {
    if (l < 0 || l >= n) {
      std::cerr << "Segtree left index " << l << " out of bounds." << std::endl;
      return;
    }
    if (r < 0 || r >= n) {
      std::cerr << "Segtree right index " << r << " out of bounds." << std::endl;
      return;
    }
    if (r > l) {
      std::cerr << "Segtree left and right indices " << l << ", " << r << " do not agree." << std::endl;
      return;
    }
  }
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