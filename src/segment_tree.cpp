#include "segment_tree.h"
#include <debug/macros.h>
#include <optional>
#include <stdexcept>

template<typename T, class F>
contest::segment_tree<T, F>::segment_tree(const std::vector<T> &a, const F &f): n(a.size()), f(f) {
  if (n > a.max_size() >> 1) {
    throw std::length_error("cannot create contest::segment_tree<T> larger than half of max_size() of std::vector<T>");
  } else if (n > 0) {
    tree = std::vector<T>(n << 1);
    std::copy(a.begin(), a.end(), tree.begin() + n);
    for (size_t i = n - 1, j = n >> (std::countr_zero(n) + 1); i > 0; i--) {
      if (i == j) {
        j >>= 1;
      } else {
        tree[i] = f(tree[i << 1], tree[i << 1 | 1]);
      }
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
std::vector<T>::const_iterator contest::segment_tree<T, F>::begin() const noexcept {
  return tree.begin() + n;
}

template<typename T, class F>
std::vector<T>::const_iterator contest::segment_tree<T, F>::end() const noexcept {
  return tree.end();
}

template<typename T, class F>
struct contest::segment_tree<T, F>::proxy {
private:
  segment_tree<T, F> *st;
  const size_t i;

public:
  // TODO: make private or move out of bounds index check here
  proxy(contest::segment_tree<T> *st, size_t i): st(st), i(i) {}

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
      st->tree[j >> 1] = st->f(st->tree[(j | 1) ^ 1], st->tree[j | 1]);
    }
    return *this;
  }
};

template<typename T, class F>
contest::segment_tree<T, F>::proxy contest::segment_tree<T, F>::operator[](size_t i) {
#ifndef ONLINE_JUDGE
  __glibcxx_check_subscript(i);
#endif

  return proxy(this, n + i);
}

template<typename T, class F>
#if __cplusplus >= 202302L
T contest::segment_tree<T, F>::operator[](size_t l, size_t r) {
#else
T contest::segment_tree<T, F>::sum(size_t l, size_t r) {
#endif
#ifndef ONLINE_JUDGE
  __glibcxx_check_subscript(l);
  __glibcxx_check_subscript(r);
  _GLIBCXX_DEBUG_VERIFY(l <= r, _M_message("left index %1; must be at most right index %2;")._M_integer(l, "#1")._M_integer(r, "#2"));
#endif

  std::optional<T> a, b;
  l += n;
  r += n + 1;
  while (l < r) {
    if (l & 1) {
      if (a.has_value()) {
        a = f(a.value(), tree[l++]);
      } else {
        a = tree[l++];
      }
    }
    if (r & 1) {
      if (b.has_value()) {
        b = f(tree[--r], b.value());
      } else {
        b = tree[--r];
      }
    }
    l >>= 1;
    r >>= 1;
  }

  if (a.has_value()) {
    if (b.has_value()) {
      return f(a.value(), b.value());
    } else {
      return a.value();
    }
  } else {
    return b.value();
  }
}
