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

Trie::~Trie() { delete root; }

Trie& Trie::operator=(const Trie& other) {
  if (this != &other) {
    // Clear current trie
    delete root;
    // Copy nodes from other trie
    root = new Node();
    *this = other;
  }
  return *this;
}

Trie& Trie::operator=(Trie&& other) noexcept {
  if (this != &other) {
    delete root;
    root = nullptr;
    std::swap(root, other.root);
  }
  return *this;
}
