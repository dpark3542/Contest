#include "segment_tree.h"
#include <debug/macros.h>
#include <stdexcept>

template<typename T, class F>
contest::segment_tree<T, F>::segment_tree(const std::vector<T> &a, const F &f): n(a.size()), f(f) {
  if (n > a.max_size() >> 1) {
    throw std::length_error("cannot create contest::segment_tree<T> larger than half of max_size() of std::vector<T>");
  } else if (n > 0) {
    tree = std::vector<T>(n << 1);
    std::copy(a.begin(), a.end(), tree.begin() + n);
    for (size_t i = n - 1; i > 0; i--) {
      tree[i] = f(tree[i << 1], tree[i << 1 | 1]);
    }
  }
}

template<typename T, class F>
contest::segment_tree<T, F>::segment_tree(const std::vector<T> &a): segment_tree(a, [](T x, T y) { return x + y; }) {}

template<typename T, class F>
size_t contest::segment_tree<T, F>::size() {
  return n;
}

template<typename T, class F>
struct contest::segment_tree<T, F>::proxy {
private:
  segment_tree<T, F> *st;
  const size_t i;

public:
  proxy(contest::segment_tree<int> *st, size_t i): st(st), i(i) {}

  operator const T& () const {
    return st->tree[i];
  }

  /**
   * Update in O(log n).
   *
   * @param t new value
   * @return
   */
  proxy& operator=(const T& t) {
    st->tree[i] = t;
    for (size_t j = i; j > 1; j >>= 1) {
      st->tree[j >> 1] = st->f(st->tree[j], st->tree[j ^ 1]);
    }
    return *this;
  }

  /**
   * Update in O(log n).
   *
   * @param t new value
   * @return
   */
  proxy& operator+=(const T& t) {
    return operator=(st->f(st->tree[i], t));
  }
};

template<typename T, class F>
contest::segment_tree<T, F>::proxy contest::segment_tree<T, F>::operator[](size_t i) {
  __glibcxx_check_subscript(i);

  return proxy(this, n + i);
}

template<typename T, class F>
#if __cplusplus >= 202302L
T contest::segment_tree<T, F>::operator[](size_t l, size_t r) {
#else
T contest::segment_tree<T, F>::sum(size_t l, size_t r) {
#endif
  __glibcxx_check_subscript(l);
  __glibcxx_check_subscript(r);
  _GLIBCXX_DEBUG_VERIFY(l <= r, _M_message("left index %1; must be at most right index %2;")._M_integer(l, "#1")._M_integer(r, "#2"));

  T res = tree[n + l];
  l += n + 1;
  r += n + 1;
  while (l < r) {
    if (l & 1) {
      res = f(res, tree[l++]);
    }
    if (r & 1) {
      res = f(res, tree[--r]);
    }
    l >>= 1;
    r >>= 1;
  }
  return res;
}
