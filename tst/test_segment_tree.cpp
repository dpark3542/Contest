#include <cassert>
#include <limits>
#include "../src/segment_tree.cpp"

unsigned long long f(unsigned long long a, unsigned long long b) {
  assert(std::countl_zero(a) + std::countr_zero(b) == std::numeric_limits<unsigned long long>::digits);
  return a ^ b;
}

void check(int n, contest::segment_tree<unsigned long long> &st) {
  assert(n == st.size());

  for (int i = 0; i < n; i++) {
    assert(1ULL << i == st[i]);

    for (int j = i; j < n; j++) {
#if __cplusplus >= 202302L
      assert((1ULL << (j + 1)) - (1ULL << i) == st[i, j]);
#else
      assert((1ULL << (j + 1)) - (1ULL << i) == st.sum(i, j));
#endif
    }
  }
}

int main() {
  for (int n = 0; n <= 63; n++) {
    std::vector<unsigned long long> a(n);
    for (int i = 0; i < n; i++) {
      a[i] = 1ULL << i;
    }
    contest::segment_tree<unsigned long long> st(a, f);
    check(n, st);

    std::vector<unsigned long long> b(n);
    contest::segment_tree<unsigned long long> st2(b);
    for (int i = 0; i < n; i++) {
      st2[i] = 1ULL << i;
    }
    check(n, st2);
  }
}
