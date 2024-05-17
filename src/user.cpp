#include "user.h"

#include "server.h"

User::User(std::string username, std::string private_key, Server* server)
    : username{username}, private_key{private_key}, server{server} {}

std::string User::get_username() const { return username; }

bool User::send_text_message(std::string text, std::string receiver) {
  std::cout << "signaature:" << std::endl;
  std::string signature = crypto::signMessage(private_key, text);
  std::cout << "signaature done" << std::endl;
  TextMessage msg{text, username, receiver};
  msg.print(std::cout);
  if (server->create_message(&msg, signature)) {
    return true;
  }
  return false;
}

bool User::send_voice_message(std::string receiver) {
  std::string voice{};
  for (std::size_t i = 0; i < 5; i++) {
    voice += std::to_string((std::rand() % 256));
  }
  std::string signature = crypto::signMessage(private_key, voice);
  VoiceMessage msg{username, receiver};
  msg.print(std::cout);
  if (server->create_message(&msg, signature)) {
    return true;
  }
  return false;
}
