#include "misc.h"
#include <debug/macros.h>

template<typename T>
std::pair<int, int> contest::binary_search(std::vector<T> &a, std::function<bool(const T&)> f) {
#ifndef ONLINE_JUDGE
  _GLIBCXX_DEBUG_VERIFY(!a.empty(), _M_message(__gnu_debug::__msg_empty));
#endif

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
