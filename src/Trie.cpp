#include "Trie.h"

Trie::Node::Node(char data, bool is_finished)
    : data{data}, is_finished{is_finished}, parent{nullptr} {
  children.fill(nullptr);
}

Trie::Node::~Node() {
  for (auto child : children) delete child;
}
