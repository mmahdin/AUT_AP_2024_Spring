#include "algebra.h"

namespace algebra {
// Define the permutations function
std::vector<std::vector<int>> permutations(std::vector<int> x) {
  if (x.size() == 1) {
    return {x};
  }

  std::vector<std::vector<int>> result;
  for (size_t i = 0; i < x.size(); ++i) {
    int first_elem = x[i];
    std::vector<int> remaining_elems = x;
    remaining_elems.erase(remaining_elems.begin() + i);
    std::vector<std::vector<int>> sub_permutations =
        permutations(remaining_elems);

    for (const auto& perm : sub_permutations) {
      std::vector<int> new_perm = {first_elem};
      new_perm.insert(new_perm.end(), perm.begin(), perm.end());
      result.push_back(new_perm);
    }
  }

  return result;
}

// Define the sgn function
int sgn(std::vector<int> ls) {
  int res = 0;
  for (size_t i = 0; i < ls.size(); ++i) {
    for (size_t j = i + 1; j < ls.size(); ++j) {
      if (ls[j] < ls[i]) {
        res++;
      }
    }
  }
  if (res % 2 == 1) {
    return -1;
  } else {
    return 1;
  }
}
}  // namespace algebra