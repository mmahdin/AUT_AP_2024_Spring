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

void Trie::insert(const std::string& str) {
  Node* node{root};
  for (char ch : str) {
    int index = ch - 'a';
    if (node->children[index] == nullptr) {
      node->children[index] = new Node(ch);
      node->children[index]->parent = node;
    }
    node = node->children[index];
  }
  node->is_finished = true;
}

bool Trie::search(const std::string& query) const {
  Node* node{root};
  for (auto ch : query) {
    int index{ch - 'a'};
    if (node->children[index] == nullptr) return 0;
    node = node->children[index];
  }
  if (node->is_finished) return 1;
  return 0;
}

bool Trie::startsWith(const std::string& prefix) const {
  Node* node{root};
  for (auto ch : prefix) {
    int index{ch - 'a'};
    if (node->children[index] == nullptr) return 0;
    node = node->children[index];
  }
  return 1;
}

void Trie::remove(const std::string& str) {
  Node* node{root};
  for (auto ch : str) {
    int index{ch - 'a'};
    node = node->children[index];
  }

  Node* parent;
  node->is_finished = false;
  for (std::size_t i{}; i < std::size(str); i++) {
    for (auto child : node->children)
      if (child != nullptr) {
        return;
        if (node->is_finished == 0) {
          parent = node->parent;
          delete node;
        }
        node = parent;
      }
  }
}

void Trie::dfs(std::function<void(Node*&)> func) {
  if (root == nullptr) return;
  std::stack<Node*> stk;
  stk.push(root);
  while (!stk.empty()) {
    Node* current = stk.top();
    stk.pop();
    func(current);
    for (auto child : current->children)
      if (child != nullptr) stk.push(child);
  }
}

void Trie::bfs(std::function<void(Node*&)> func) {
  if (root == nullptr) return;
  std::queue<Node*> q;
  q.push(root);
  while (!q.empty()) {
    Node* current = q.front();
    q.pop();
    func(current);
    for (auto child : current->children)
      if (child != nullptr) q.push(child);
  }
}
