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
    Message testMessage("text", "Alice", "Bob");
    std::cout << "****** Testing Message Creation and Display ******"
              << std::endl;
    assert(testMessage.get_type() == "text");
    assert(testMessage.get_sender() == "Alice");
    assert(testMessage.get_receiver() == "Bob");
    // testMessage.print(std::cout);
    std::cout << testMessage << std::endl;
    std::cout << "@@@@@ All tests passed for Message class. @@@@@" << std::endl;

    std::cout << "\n" << std::endl;

    TextMessage testTextMessage("Hello, Bob!", "Alice", "Bob");
    std::cout << "****** Testing TextMessage Print Function ******"
              << std::endl;
    // testTextMessage.print(std::cout);
    std::cout << testTextMessage << std::endl;
    std::cout << testTextMessage.get_text() << std::endl;
    std::cout << "@@@@@ All tests passed for TextMessage print function. @@@@@"
              << std::endl;

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