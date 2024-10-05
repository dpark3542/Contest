#include <cassert>
#include <functional>
#include <optional>
#include <vector>

namespace contest {
  template<typename T, class F = std::function<T(const T&, const T&)>>
  class segment_tree {
  private:
    const size_t n;
    const F f;
    std::vector<T> tree;

  public:
    explicit segment_tree(const std::vector<T> &a, const F &f): n(a.size()), f(f) {
      assert(n <= a.max_size() >> 1);

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

    size_t size() {
      return n;
    }

    std::vector<T>::const_iterator begin() const noexcept {
      return tree.begin() + n;
    }

    std::vector<T>::const_iterator end() const noexcept {
      return tree.end();
    }

    T get(size_t i) const {
      return tree[i + n];
    }

    void update(size_t i, T &t) {
      tree[i] = t;
      for (size_t j = i; j > 1; j >>= 1) {
        tree[j >> 1] = f(tree[(j | 1) ^ 1], tree[j | 1]);
      }
    }

    T sum(size_t l, size_t r) {
      assert(0 <= l && l <= r && r < n);

      std::optional<T> a, b;
      l += n;
      r += n + 1;
      while (l < r) {
        if (l & 1) {
          a = a.has_value() ? f(a.value(), tree[l++]) : tree[l++];
        }
        if (r & 1) {
          b = b.has_value() ? f(tree[--r], b.value()) : tree[--r];
        }
        l >>= 1;
        r >>= 1;
      }

      if (a.has_value()) {
        return b.has_value() ? f(a.value(), b.value()) : a.value();
      } else {
        return b.value();
      }
    }
  };
}
