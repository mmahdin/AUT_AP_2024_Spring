#ifndef USER_H
#define USER_H

#include <string>

class Server;

class User {
 public:
  // Constructor
  User(std::string username, std::string private_key, Server* server);

  // Getter for username
  std::string get_username() const;

  // Functions to send messages
  bool send_text_message(std::string text, std::string receiver);
  bool send_voice_message(std::string receiver);

 private:
  std::string username;     // Username of the user
  std::string private_key;  // Private RSA key of the user
  Server* const server;     // Pointer to the server for communications
};

#endif  // USER_H