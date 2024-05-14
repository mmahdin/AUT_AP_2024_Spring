#include <gtest/gtest.h>

#include <iostream>

#include "message.h"
// #include "server.h"
// #include "stl.h"
// #include "user.h"

int main(int argc, char **argv) {
  if (true)  // make false to run unit-tests
  {
    // debug section
    Message msg{"salam", "man", "mahdi"};
    std::cout << msg << std::endl;
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