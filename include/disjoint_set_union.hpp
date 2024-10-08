#include <cassert>
#include <vector>

namespace contest {
  class disjoint_set_union {
  private:
    size_t ccount;
    std::vector<size_t> parent, csize;

    size_t root(size_t x) {
      assert(0 <= x && x < parent.size());

      size_t root = x;
      while (parent[root] != root) {
        root = parent[root];
      }
      while (parent[x] != root) {
        size_t p = parent[x];
        parent[x] = root;
        x = p;
      }
      return root;
    }

  public:
    explicit disjoint_set_union(size_t n): ccount(n) {
      parent = std::vector<size_t>(n);
      for (int i = 0; i < n; i++) {
        parent[i] = i;
      }
      csize = std::vector<size_t>(n, 1);
    }

    size_t component_size(size_t x) {
      return csize[root(x)];
    }

    size_t component_count() const {
      return ccount;
    }

    bool is_connected(size_t x, size_t y) {
      return root(x) == root(y);
    }

    void merge(size_t x, size_t y) {
      x = root(x);
      y = root(y);
      if (x != y) {
        if (csize[x] < csize[y]) {
          std::swap(x, y);
        }
        parent[y] = x;
        csize[x] += csize[y];
        ccount--;
      }
    }
  };
}
