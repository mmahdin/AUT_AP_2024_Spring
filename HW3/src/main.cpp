#include <gtest/gtest.h>

#include <iostream>

// #include "BloomFilter.h"
// #include "Trie.h"
#include <vector>

int main(int argc, char **argv) {
  if (true)  // Set to false to run unit-tests
  {
    // Debug section: Place your debugging code here

    std::vector<std::size_t> seeds;
    for (std::size_t i{}; i < 100; seeds.push_back(i), i++)
      ;
  } else {
    ::testing::InitGoogleTest(&argc, argv);
    std::cout << "RUNNING TESTS ..." << std::endl;
    int ret{RUN_ALL_TESTS()};
    if (!ret)
      std::cout << "<<<SUCCESS>>>" << std::endl;
    else
      std::cout << "FAILED" << std::endl;
  }
  return 0;
}
