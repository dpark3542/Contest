#pragma once

#include <cassert>
#include <numeric>
#include <vector>

namespace contest {
  class disjoint_set_union {
  private:
    size_t c;
    std::vector<size_t> p, s;

    size_t root(const size_t x) {
      assert(x < p.size());

      size_t r = x;
      while (p[r] != r) {
        r = p[r];
      }

      for (size_t y = x; p[y] != r;) {
        const size_t q = p[y];
        p[y] = r;
        y = q;
      }

      return r;
    }

  public:
    explicit disjoint_set_union(const size_t n): c(n) {
      p = std::vector<size_t>(n);
      std::iota(p.begin(), p.end(), 0);
      s = std::vector<size_t>(n, 1);
    }

    size_t component_size(const size_t x) {
      return s[root(x)];
    }

    size_t component_count() const {
      return c;
    }

    size_t vertex_count() const {
      return p.size();
    }

    bool connected(const size_t x, const size_t y) {
      return root(x) == root(y);
    }

    void add_vertex() {
      p.push_back(p.size());
      s.push_back(1);
      c++;
    }

    void add_edge(const size_t x, const size_t y) {
      const size_t u = root(x), v = root(y);
      if (u != v) {
        if (s[u] < s[v]) {
          p[v] = u;
          s[u] += s[v];
        } else {
          p[u] = v;
          s[v] += s[u];
        }
        c--;
      }
    }
  };
}
