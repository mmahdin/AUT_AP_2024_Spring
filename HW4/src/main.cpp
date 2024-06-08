#include <gtest/gtest.h>

#include <cassert>
#include <iostream>
#include <vector>

#include "crypto.h"
#include "message.h"
#include "server.h"
#include "stl.h"
#include "user.h"

void test_initial_vector_with_3_multiples() {
  std::vector<int> v;
  initial_vector_with_3_multiples(v, 5);
  std::vector<int> expected = {3, 6, 9, 12, 15};
  assert(v == expected);

  initial_vector_with_3_multiples(v, 0);
  expected = {};
  assert(v == expected);

  initial_vector_with_3_multiples(v, 1);
  expected = {3};
  assert(v == expected);

  std::cout << "All tests for initial_vector_with_3_multiples passed!"
            << std::endl;
}

void test_count_unique_above() {
  std::vector<int> v = {1, 2, 3, 4, 5, 5, 6, 7, 8, 8, 9, 10};
  assert(count_unique_above(v, 5) == 5);
  assert(count_unique_above(v, 8) == 2);
  assert(count_unique_above(v, 10) == 0);
  assert(count_unique_above(v, 0) == 10);

  v = {5, 5, 5, 5, 5};
  assert(count_unique_above(v, 4) == 1);
  assert(count_unique_above(v, 5) == 0);

  std::cout << "All tests for count_unique_above passed!" << std::endl;
}

void test_vector_to_string() {
  std::vector<int> v = {1, 2, 3, 4, 5};
  assert(vector_to_string(v, '-') == "5-4-3-2-1");
  assert(vector_to_string(v, ',') == "5,4,3,2,1");

  v = {10};
  assert(vector_to_string(v, '-') == "10");

  v = {};
  assert(vector_to_string(v, '-') == "");

  std::cout << "All tests for vector_to_string passed!" << std::endl;
}

void test_square_elements() {
  std::vector<int> v = {1, 2, 3, 4, 5};
  square_elements(v);
  std::vector<int> expected = {1, 4, 9, 16, 25};
  assert(v == expected);

  v = {0, -1, -2};
  square_elements(v);
  expected = {0, 1, 4};
  assert(v == expected);

  v = {};
  square_elements(v);
  expected = {};
  assert(v == expected);

  std::cout << "All tests for square_elements passed!" << std::endl;
}

void test_copy_if_even() {
  std::vector<int> source = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::vector<int> destination;
  copy_if_even(source, destination);
  std::vector<int> expected = {2, 4, 6, 8, 10};
  assert(destination == expected);

  source = {1, 3, 5, 7, 9};
  destination.clear();
  copy_if_even(source, destination);
  expected = {};
  assert(destination == expected);

  source = {2, 4, 6, 8, 10};
  destination.clear();
  copy_if_even(source, destination);
  expected = {2, 4, 6, 8, 10};
  assert(destination == expected);

  std::cout << "All tests for copy_if_even passed!" << std::endl;
}

int main(int argc, char** argv) {
  if (false)  // make false to run unit-tests
  {
    // debug section
    // Message testMessage("text", "Alice", "Bob");
    // std::cout << "****** Testing Message Creation and Display ******"
    //           << std::endl;
    // assert(testMessage.get_type() == "text");
    // assert(testMessage.get_sender() == "Alice");
    // assert(testMessage.get_receiver() == "Bob");
    // // testMessage.print(std::cout);
    // std::cout << testMessage << std::endl;
    // std::cout << "@@@@@ All tests passed for Message class. @@@@@" <<
    // std::endl;

    // std::cout << "\n" << std::endl;

    // TextMessage testTextMessage("Hello, Bob!", "Alice", "Bob");
    // std::cout << "****** Testing TextMessage Print Function ******"
    //           << std::endl;
    // // testTextMessage.print(std::cout);
    // std::cout << testTextMessage << std::endl;
    // std::cout << testTextMessage.get_text() << std::endl;
    // std::cout << "@@@@@ All tests passed for TextMessage print function.
    // @@@@@"
    //           << std::endl;

    // VoiceMessage testVoiceMessage("Alice", "Bob");
    // std::cout << "****** Testing VoiceMessage Functionality ******"
    //           << std::endl;
    // std::cout << testVoiceMessage << std::endl;
    // std::cout << "@@@@@ All tests passed for VoiceMessage class. @@@@@"
    //           << std::endl;

    // std::cout << "****** crypto ******" << std::endl;
    // std::string public_key, private_key;
    // crypto::generate_key(public_key, private_key);
    // std::string text = "hello";
    // std::string signature = crypto::signMessage(private_key, text);
    // std::cout << "@@@@@ crypto done @@@@@" << std::endl;

    std::cout << "****** send text message ******" << std::endl;
    std::cout << std::endl;
    Server* server{new Server()};
    User mahdi = server->create_user("mahdi");
    User ali = server->create_user("ali");

    bool check = mahdi.send_text_message("hello", "ali");
    std::cout << "Check 1: " << check << std::endl;
    bool check2 = mahdi.send_voice_message("ali");
    std::cout << "Check 2: " << check2 << std::endl;
    std::cout << std::endl;
    std::cout << "@@@@@ All tests passed for VoiceMessage class. @@@@@"
              << std::endl;

    test_initial_vector_with_3_multiples();
    test_count_unique_above();
    test_vector_to_string();
    test_square_elements();
    test_copy_if_even();

    std::cout << "All tests passed!" << std::endl;

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