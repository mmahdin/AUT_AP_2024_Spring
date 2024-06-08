#include "user.h"

#include "server.h"

User::User(std::string username, std::string private_key, Server* server)
    : username{username}, private_key{private_key}, server{server} {}

std::string User::get_username() const { return username; }

bool User::send_text_message(std::string text, std::string receiver) {
  std::vector<User> users{server->get_users()};
  auto it = std::find_if(users.begin(), users.end(), [&receiver](const User& user) {
        return user.get_username() == receiver;
    });
  if (it == users.end()) {
    return 0;
  }
  std::string signature = crypto::signMessage(private_key, text);
  TextMessage* msg = new TextMessage{text, username, receiver};
  if (server->create_message(msg, signature)) {
    return true;
  }
  return false;
}

bool User::send_voice_message(std::string receiver) {
  VoiceMessage* msg = new VoiceMessage{username, receiver};
  std::string signature = crypto::signMessage(private_key, msg->get_text());
  if (server->create_message(msg, signature)) {
    return true;
  }
  return false;
}
