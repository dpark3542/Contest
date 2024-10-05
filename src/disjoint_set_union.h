#ifndef CONTEST_DISJOINT_SET_UNION_H
#define CONTEST_DISJOINT_SET_UNION_H

#include <vector>

namespace contest {
  class disjoint_set_union {
  private:
    size_t ccount;
    std::vector<size_t> parent, csize;
    size_t root(size_t x);

  public:
    explicit disjoint_set_union(size_t n);
    size_t component_size(size_t x);
    size_t component_count() const;
    bool is_connected(size_t x, size_t y);
    void merge(size_t x, size_t y);
  };
}

#endif //CONTEST_DISJOINT_SET_UNION_H
