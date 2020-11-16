#include <chrono>
#include <vector>
#include <ext/pb_ds/assoc_container.hpp>

#ifndef CONTEST_MISC_H
#define CONTEST_MISC_H

#define min(x,y) ((x) < (y) ? (x) : (y))
#define max(x,y) ((x) > (y) ? (x) : (y))

namespace contest {
  struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
      // http://xorshift.di.unimi.it/splitmix64.c
      x += 0x9e3779b97f4a7c15;
      x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
      x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
      return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
      static const uint64_t FIXED_RANDOM = std::chrono::steady_clock::now().time_since_epoch().count();
      return splitmix64(x + FIXED_RANDOM);
    }
  };

  template<typename K, typename V>
  using hash_table = __gnu_pbds::gp_hash_table<K, V, custom_hash>;
}

#endif //CONTEST_MISC_H
