#pragma once

#include <string>
#include <vector>

namespace contest {
  inline std::vector<int> z(const std::string &s) {
    if (s.empty()) {
      return {};
    }

    int n = static_cast<int> (s.size());
    std::vector<int> z(n);
    z[0] = n;
    for (int i = 1, l = 0, r = 0; i < n; i++) {
      z[i] = i < r ? std::min(r - i, z[i - l]) : 0;
      while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
        z[i]++;
      }
      if (i + z[i] > r) {
        l = i;
        r = i + z[i];
      }
    }
    return z;
  }
}
