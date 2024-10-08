#include <cassert>
#include <functional>
#include <vector>

namespace contest {
  template<typename T>
  std::pair<int, int> binary_search(std::vector <T> &a, std::function<bool(const T &)> f) {
    assert(!a.empty());

    if (!f(a[0])) {
      return {-1, 0};
    } else if (f(a.back())) {
      return {a.size() - 1, a.size()};
    } else {
      int l = 0, r = a.size() - 1;
      while (l + 1 < r) {
        int m = (l + r) / 2;
        if (f(m)) {
          l = m;
        } else {
          r = m;
        }
      }
      return {l, r};
    }
  }
}
