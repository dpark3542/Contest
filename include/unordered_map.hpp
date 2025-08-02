#pragma once

#ifdef __GNUC__
#include <chrono>
#include <ext/pb_ds/assoc_container.hpp>

namespace contest {
  struct custom_hash {
    // http://xorshift.di.unimi.it/splitmix64.c
    size_t operator()(uint64_t x) const {
      static const uint64_t FIXED_RANDOM = std::chrono::steady_clock::now().time_since_epoch().count();
      x += FIXED_RANDOM;
      x += 0x9e3779b97f4a7c15;
      x = (x ^ x >> 30) * 0xbf58476d1ce4e5b9;
      x = (x ^ x >> 27) * 0x94d049bb133111eb;
      return x ^ x >> 31;
    }
  };

  template<typename K, typename V>
  using unordered_map = __gnu_pbds::gp_hash_table<K, V, custom_hash>;
}
#endif
