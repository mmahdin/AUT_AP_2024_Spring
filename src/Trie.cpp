#include "Trie.h"

Trie::Node::Node(char data, bool is_finished)
    : data{data}, is_finished{is_finished}, parent{nullptr} {
  children.fill(nullptr);
}

Trie::Node::~Node() {
  for (auto child : children) delete child;
}

Trie::Trie() : root{new Node()} {}

Trie::Trie(const Trie& other) {
  root = new Node();
  //   *this = other;
  root = other.root;
}

Trie::Trie(Trie&& other) {
  root = new Node();
  root = other.root;
  delete other.root;
  //   std::swap(root, other.root);
}

Trie::Trie(std::initializer_list<std::string> list) : root{new Node()} {
  for (const auto& word : list) {
    insert(word);
  }
}