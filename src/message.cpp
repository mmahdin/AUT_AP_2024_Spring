#include "message.h"

Message::Message(std::string type, std::string sender, std::string receiver)
    : type{type}, sender{sender}, receiver{receiver} {
  std::time_t currentTime = std::time(nullptr);
  time = std::ctime(&currentTime);
}

Message::Message() : Message{"", "", ""} {}

std::string Message::get_type() const { return type; }

std::string Message::get_sender() const { return sender; }

std::string Message::get_receiver() const { return receiver; }

std::string Message::get_time() const { return time; }

void Message::print(std::ostream& os) const {
  os << "*************************\n"
     << sender << "->" << receiver << "\n"
     << "message type: " << type << "\n"
     << "message time:" << time << "*************************" << std::endl;
}

std::ostream& operator<<(std::ostream& os, const Message& msg) {
  msg.print(os);
  return os;
}

TextMessage::TextMessage(std::string text, std::string sender,
                         std::string receiver)
    : Message("Text", sender, receiver), text{text} {}

void TextMessage::print(std::ostream& os) const {
  os << "*************************\n"
     << get_sender() << "->" << get_receiver() << "\n"
     << "message type: " << get_type() << "\n"
     << "message time:" << get_time() << "text: " << text
     << "\n*************************" << std::endl;
}

std::string TextMessage::get_text() const { return text; }
