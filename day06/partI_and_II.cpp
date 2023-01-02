#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

typedef int window_size_t;

template <typename T>
typename std::enable_if_t<!std::is_integral<T>::value> modulo_incr(T &numeric,
                                                                   T mod) {}

template <typename T>
typename std::enable_if_t<std::is_integral<T>::value> modulo_incr(T &numeric,
                                                                  T mod) {
  numeric = (++numeric) % mod;
}

template <typename T>
bool contains_duplicates(std::vector<T> vec) {
  std::vector<char> sorted(vec.begin(), vec.end());
  std::sort(sorted.begin(), sorted.end());

  for (window_size_t i = 0; i < vec.size() - 1; ++i) {
    if (sorted[i] == sorted[i + 1]) {
      return true;
    }
  }

  return false;
}

int main() {
  std::ifstream datastream("datastream.txt");

  // Part I
  const window_size_t window_size = 4;
  // Part II
  // const window_size_t window_size = 14;

  std::vector<char> sliding_window(window_size);
  window_size_t newest_idx = window_size - 1;
  window_size_t oldest_idx = 0;
  uint64_t marker = 1;

  while (datastream >> sliding_window[oldest_idx]) {

    if (!contains_duplicates(sliding_window) &&
        marker >= window_size) {
      break;
    }

    modulo_incr(newest_idx, window_size);
    modulo_incr(oldest_idx, window_size);
    marker++;
  }

  std::cout << marker << std::endl;

  return 0;
}
