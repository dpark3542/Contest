#include "disjoint_set_union.h"
#include <debug/macros.h>

size_t contest::disjoint_set_union::root(size_t x) {
#ifndef ONLINE_JUDGE
  _GLIBCXX_DEBUG_VERIFY(x < parent.size(), _M_message(__gnu_debug::__msg_subscript_oob)._M_sequence(*this, "this")._M_integer(x, "#1")._M_integer(parent.size(), "size"));
#endif

  size_t root = x;
  while (parent[root] != root) {
    root = parent[root];
  }
  while (parent[x] != root) {
    size_t p = parent[x];
    parent[x] = root;
    x = p;
  }
  return root;
}

contest::disjoint_set_union::disjoint_set_union(size_t n): ccount(n) {
  parent = std::vector<size_t>(n);
  for (int i = 0; i < n; i++) {
    parent[i] = i;
  }
  csize = std::vector<size_t>(n, 1);
}

size_t contest::disjoint_set_union::component_size(size_t x) {
  return csize[root(x)];
}

size_t contest::disjoint_set_union::component_count() const {
  return ccount;
}

bool contest::disjoint_set_union::is_connected(size_t x, size_t y) {
  return root(x) == root(y);
}

void contest::disjoint_set_union::merge(size_t x, size_t y) {
  x = root(x);
  y = root(y);
  if (x != y) {
    if (csize[x] < csize[y]) {
      std::swap(x, y);
    }
    parent[y] = x;
    csize[x] += csize[y];
    ccount--;
  }
}
