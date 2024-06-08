#include "server.h"

Server::Server() {}

std::vector<User> Server::get_users() const { return users; }

std::map<std::string, std::string> Server::get_public_keys() const {
  return public_keys;
}

std::vector<Message*> Server::get_messages() const { return messages; }

User Server::create_user(std::string username) {
  // first opeiton
  for (auto i : users)
    if (i.get_username() == username)
      throw std::logic_error("The user already exist\n");

  // second option
  // if (std::find(users.begin(), users.end(), username) != users.end())
  //   throw std::logic_error("The user already exist\n");

  std::string public_key{}, private_key{};
  crypto::generate_key(public_key, private_key);
  User new_user{username, private_key, this};
  users.push_back(new_user);
  public_keys[username] = public_key;
  return new_user;
}

bool Server::create_message(Message* msg, std::string signature) {
  bool authentic = crypto::verifySignature(public_keys[msg->get_sender()],
                                           msg->get_text(), signature);
  if (authentic) {
    messages.push_back(msg);
    return true;
  }
  return false;
}

std::vector<Message*> Server::get_all_messages_from(std::string username) {
  std::vector<Message*> result;
  for (auto* msg : messages) {
    if (msg->get_sender() == username) {
      result.push_back(msg);
    }
  }
  return result;
}

std::vector<Message*> Server::get_all_messages_to(std::string username) {
  std::vector<Message*> result;
  for (auto* msg : messages) {
    if (msg->get_receiver() == username) {
      result.push_back(msg);
    }
  }
  return result;
}

std::vector<Message*> Server::get_chat(std::string user1, std::string user2) {
  std::vector<Message*> result;
  for (auto* msg : messages) {
    if ((msg->get_sender() == user1 && msg->get_receiver() == user2) ||
        (msg->get_sender() == user2 && msg->get_receiver() == user1)) {
      result.push_back(msg);
    }
  }
  return result;
}

void Server::sort_msgs(std::vector<Message*> msgs) {
  std::sort(msgs.begin(), msgs.end(), [](const Message* a, const Message* b) {
    return a->get_time() < b->get_time();
  });
}
