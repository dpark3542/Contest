#include <cassert>
#include <iostream>
#include <limits>
#include "../src/segment_tree.cpp"

void check(int n, contest::segment_tree<unsigned int> &st) {
  assert(n == st.size());

  for (int i = 0; i < n; i++) {
    assert(1 << i == st[i]);

    for (int j = i; j < n; j++) {
#if __cplusplus >= 202302L
      assert((1 << (j + 1)) - (1 << i) == st[i, j]);
#else
      assert((1 << (j + 1)) - (1 << i) == st.sum(i, j));
#endif
    }
  }
}

int main() {
  for (int n = 0; n <= 17; n++) {
    std::vector<unsigned int> a(n);
    for (int i = 0; i < n; i++) {
      a[i] = 1 << i;
    }
    contest::segment_tree<unsigned int> st(a);
    check(n, st);

    std::vector<unsigned int> b(n);
    contest::segment_tree<unsigned int> st2(b);
    for (int i = 0; i < n; i++) {
      st2[i] = 1 << i;
    }
    check(n, st2);
  }
}
