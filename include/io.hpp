#pragma once

#include <ostream>
#include <ranges>

template <std::ranges::range R>
std::ostream& operator<<(std::ostream& out, const R& r) {
  for (auto& x : r) {
    out << x << ' ';
  }
  return out;
}
