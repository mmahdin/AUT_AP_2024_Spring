#include "user.h"

#include "server.h"

User::User(std::string username, std::string private_key, Server* server)
    : username{username}, private_key{private_key}, server{server} {}

std::string User::get_username() const { return username; }

bool User::send_text_message(std::string text, std::string receiver) {
  std::string signature = crypto::signMessage(private_key, text);
  TextMessage msg{text, username, receiver};
  if (server->create_message(&msg, signature)) {
    return true;
  }
  return false;
}

bool User::send_voice_message(std::string receiver) {
  VoiceMessage msg{username, receiver};
  std::cout << "message in send voice message: " << msg.get_text();
  std::string signature = crypto::signMessage(private_key, msg.get_text());
  if (server->create_message(&msg, signature)) {
    return true;
  }
  return false;
}
