#pragma once

#include <functional>
#include <vector>
#include <queue>

namespace contest {
  template<typename T>
  const T& mod(const T& x, const T& y) {
    return (x % y + y) % y;
  }

  template<typename T>
  const T& ceil(const T& x, const T& y) {
    return (x + y - 1) / y;
  }

  template<typename T>
  using max_priority_queue = std::priority_queue<T, std::vector<T>, std::less<T>>;

  template<typename T>
  using min_priority_queue = std::priority_queue<T, std::vector<T>, std::greater<T>>;
}
