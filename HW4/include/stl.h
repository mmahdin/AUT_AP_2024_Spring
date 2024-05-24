#ifndef STL_H
#define STL_H

#include <algorithm>
#include <iterator>
#include <numeric>
#include <set>
#include <string>
#include <vector>

inline void initial_vector_with_3_multiples(std::vector<int>& v, size_t size);
inline int count_unique_above(std::vector<int> v, int n);
inline std::string vector_to_string(std::vector<int> v, char separator);
inline void square_elements(std::vector<int>& v);
inline void copy_if_even(const std::vector<int>& source,
                         std::vector<int>& destination);

void initial_vector_with_3_multiples(std::vector<int>& v, size_t size) {
  v.resize(size);
  int multiple = 0;
  std::generate(v.begin(), v.end(), [&multiple]() {
    multiple += 3;
    return multiple;
  });
}

int count_unique_above(std::vector<int> v, int n) {
  std::set<int> unique_elements(v.begin(), v.end());
  return std::count_if(unique_elements.begin(), unique_elements.end(),
                       [n](int x) { return x > n; });
}

std::string vector_to_string(std::vector<int> v, char separator) {
  std::reverse(v.begin(), v.end());
  return std::accumulate(v.begin(), v.end(), std::string(),
                         [separator](const std::string& a, int b) {
                           return a.empty() ? std::to_string(b)
                                            : a + separator + std::to_string(b);
                         });
}

void square_elements(std::vector<int>& v) {
  std::transform(v.begin(), v.end(), v.begin(), [](int x) { return x * x; });
}

void copy_if_even(const std::vector<int>& source,
                  std::vector<int>& destination) {
  std::copy_if(source.begin(), source.end(), std::back_inserter(destination),
               [](int x) { return x % 2 == 0; });
}

#endif  // STL_H