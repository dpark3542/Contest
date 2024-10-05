#ifndef CONTEST_SEGMENT_TREE_H
#define CONTEST_SEGMENT_TREE_H

#include <vector>
#include <functional>

namespace contest {
  /**
   * Implementation of segment tree from https://codeforces.com/blog/entry/18051
   *
   * @tparam T type
   */
  template<typename T, class F = std::function<T(const T&, const T&)>>
  class segment_tree {
  private:
    const size_t n;
    const F f;
    std::vector<T> tree;

  public:
    /**
     * Construct in O(n).
     *
     * @param a base vector
     * @param f associative, binary operator
     */
    explicit segment_tree(const std::vector<T> &a, const F &f);

    /**
     * Construct in O(n).
     *
     * @param a base vector
     */
    explicit segment_tree(const std::vector<T> &a);

    size_t size();
    std::vector<T>::const_iterator begin() const noexcept;
    std::vector<T>::const_iterator end() const noexcept;

    struct proxy;
    /**
     * Access in O(1).
     *
     * @param i index
     * @return element
     */
    proxy operator[](size_t i);

    /**
     * Sums t[l] + ... + t[r] in O(log n) time.
     *
     * @tparam T type
     * @param l left index
     * @param r right index
     * @return inclusive sum
     */
#if __cplusplus >= 202302L
    T operator[](size_t l, size_t r);
#else
    T sum(size_t l, size_t r);
#endif
  };
}



#endif //CONTEST_SEGMENT_TREE_H
