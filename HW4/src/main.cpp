#include <gtest/gtest.h>

#include <iostream>

#include "crypto.h"
#include "message.h"
#include "server.h"
// #include "stl.h"
#include "user.h"

int main(int argc, char** argv) {
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

    VoiceMessage testVoiceMessage("Alice", "Bob");
    std::cout << "****** Testing VoiceMessage Functionality ******"
              << std::endl;
    std::cout << testVoiceMessage << std::endl;
    std::cout << "@@@@@ All tests passed for VoiceMessage class. @@@@@"
              << std::endl;

    std::cout << "****** crypto ******" << std::endl;
    std::string public_key, private_key;
    crypto::generate_key(public_key, private_key);
    std::string text = "hello";
    std::string signature = crypto::signMessage(private_key, text);
    std::cout << "@@@@@ crypto done @@@@@" << std::endl;

    std::cout << "****** send text message ******" << std::endl;
    Server* server{new Server()};
    server->create_user("mahdi");
    server->create_user("ali");
    crypto::generate_key(public_key, private_key);
    User mahdi{"mahdi", private_key, server};
    User ali{"ali", private_key, server};
    bool check = mahdi.send_text_message("hello", "ali");
    std::cout << "check: " << check << std::endl;
    bool check2 = mahdi.send_voice_message("ali");
    std::cout << "check2: " << check2 << std::endl;
    std::cout << "@@@@@ All tests passed for VoiceMessage class. @@@@@"
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