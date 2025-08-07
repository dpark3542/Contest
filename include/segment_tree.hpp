#pragma once

#include <algorithm>
#include <cassert>
#include <vector>

// Adapted from: https://codeforces.com/blog/entry/18051
namespace contest {
  template<typename T>
  class segment_tree {
  private:
    T (* const f)(T, T);
    std::vector<T> a;
    const size_t n;

  public:
    segment_tree(const size_t n, T (*f)(T, T)): f(f), a(std::vector<T>(n << 1)), n(n) {

    }

    template<typename InputIt>
    segment_tree(InputIt first, InputIt last, T (*f)(T, T)): f(f), a(std::vector<T>(first, last)), n(a.size()) {
      a.resize(n << 1);
      std::rotate(a.begin(), a.begin() + n, a.end());
      for (size_t i = n - 1; i > 0; i--) {
        a[i] = f(a[i << 1], a[i << 1 | 1]);
      }
    }

    [[nodiscard]] size_t size() const {
      return n;
    }

    typename std::vector<T>::const_iterator begin() const noexcept {
      return a.begin() + n;
    }

    typename std::vector<T>::const_iterator end() const noexcept {
      return a.end();
    }

    const T& operator[](const size_t i) const {
      assert(i < n);

      return a[i + n];
    }

    const T& front() const {
      return a[n];
    }

    const T& back() const {
      return a.back();
    }

    class proxy {
    private:
      segment_tree &st;
      const size_t i;

      void propagate() const {
        for (size_t j = i; j > 1; j >>= 1) {
          st.a[j >> 1] = st.f(st.a[j], st.a[j ^ 1]);
        }
      }
    public:
      proxy(segment_tree &st, const size_t i): st(st), i(i) {

      }

      explicit operator T() const {
        return st.a[i];
      }

      proxy& operator=(const T& x) {
        st.a[i] = x;
        propagate();
        return *this;
      }

      proxy& operator+=(const T& x) requires requires(T x, T y) { x += y; } {
        st.a[i] += x;
        propagate();
        return *this;
      }

      proxy& operator++(T) requires requires(T x) { ++x; } {
        ++st.a[i];
        propagate();
        return *this;
      }

      proxy operator++() requires requires(T x) { x++; } {
        st.a[i]++;
        propagate();
        return *this;
      }

      proxy& operator-=(const T& x) requires requires(T x, T y) { x -= y; } {
        st.a[i] -= x;
        propagate();
        return *this;
      }

      proxy& operator--(T) requires requires(T x) { x--; } {
        --st.a[i];
        propagate();
        return *this;
      }

      proxy operator--() requires requires(T x) { --x; } {
        st.a[i]--;
        propagate();
        return *this;
      }

      bool operator==(T& x) const requires requires(T x, T y) { x == y; } {
        return st.a[i] == x;
      }

      auto operator<=>(T& x) const requires requires(T x, T y) { x <=> y; } {
        return st.a[i] <=> x;
      }

      friend std::ostream& operator<<(std::ostream &out, const proxy &p) {
        return out << p.st.a[p.i];
      }
    };

    proxy operator[](const size_t i) {
      assert(i < n);

      return proxy(*this, i + n);
    }

    proxy front() {
      return proxy(*this, n);
    }

    proxy back() {
      return proxy(*this, (n << 1) - 1);
    }

    T operator[](size_t l, size_t r) const {
      assert(l <= r && r < n);

      T res{};
      l += n;
      r += n + 1;
      while (l < r) {
        if (l & 1) {
          res = f(res, a[l++]);
        }
        l >>= 1;

        if (r & 1) {
          res = f(a[--r], res);
        }
        r >>= 1;
      }

      return res;
    }
  };
}
