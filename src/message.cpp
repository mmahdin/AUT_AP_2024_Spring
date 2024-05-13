#include "message.h"

Message::Message(std::string type, std::string sender, std::string receiver)
    : type{type}, sender{sender}, receiver{receiver} {
  this->time = std::to_string(std::time(nullptr));
}
