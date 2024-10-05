#ifndef CONTEST_MISC_H
#define CONTEST_MISC_H

#include <vector>
#include <functional>

#define mod(x, y) ((x % y + y) % y)
#define ceil(x, y) ((x + y - 1) / y)

namespace contest {
  template<typename T>
  std::pair<int, int> binary_search(std::vector<T> &a, std::function<bool(const T&)> f);
}

#endif //CONTEST_MISC_H
