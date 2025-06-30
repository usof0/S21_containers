#ifndef S21_TREE_H
#define S21_TREE_H

#include <iostream>
#include <optional>
#include <utility>  // std::pair

template <typename Key, typename Value>
class RBTree {
 private:
  enum Color { RED, BLACK };
  struct Node {
    Key key;
    Value value;
    Node* left;
    Node* right;
    Node* parent;
    Color color;
    Node(Key k, Value v, Color c = RED)
        : key(k),
          value(v),
          left(nullptr),
          right(nullptr),
          parent(nullptr),
          color(c) {}
  };

  // Приватные методы класса
  void leftRotate(Node* node);
  void rightRotate(Node* node);
  void insertFixup(Node* node);
  Node* minimum(Node* node) const;
  Node* maximum(Node* node) const;
  void transplant(Node* first_node, Node* second_node);
  void deleteFixup(Node* node);
  Node* copySubtree(Node* node, Node* parent);
  void handleBrother(Node* node, Node* brother);

 protected:
  Node* root;
  size_t node_count;
  Node* findNode(const Key& key) const;

 public:
  using key_type = Key;
  using value_type = Value;
  using size_type = size_t;

  // Конструкторы и деструктор
  RBTree();
  RBTree(const RBTree& other);
  RBTree(RBTree&& other) noexcept;
  RBTree& operator=(const RBTree& other);
  RBTree& operator=(RBTree&& other) noexcept;
  ~RBTree();
  void clear(Node* node);

  // Публичные методы класса
  std::pair<Node*, bool> insert(const Key& key, const Value& value);
  std::pair<Node*, bool> insertMulti(const Key& key, const Value& value);
  void erase(const Key& key);
  bool contains(const Key& key) const;
  void print() const;
  void printTree(Node* node, char prefix[], bool isLeft) const;
  size_type size() const;
  Value& at(const Key& key);
  const Value& at(const Key& key) const;
  Value& getOrInsert(const Key& key);
  size_type count(const Key& key) const {
    size_type count = 0;
    for (auto it = begin(); it != end(); ++it) {
      if (*it == key) ++count;
    }
    return count;
  }

  // Итератор
  class iterator {
   private:
    Node* current;
    Node* root;
    Node* treeMinimum(Node* node) const;
    Node* treeMaximum(Node* node) const;
    Node* successor(Node* node) const;
    Node* predecessor(Node* node) const;

   public:
    iterator(Node* root = nullptr, Node* start = nullptr)
        : current(start), root(root) {}
    iterator& operator++() {
      current = successor(current);
      return *this;
    }
    iterator operator++(int) {
      iterator temp = *this;
      current = successor(current);
      return temp;
    }
    iterator& operator--() {
      if (current == nullptr) {
        current = treeMaximum(root);
      } else {
        current = predecessor(current);
      }
      return *this;
    }
    iterator operator--(int) {
      iterator temp = *this;
      if (current == nullptr) {
        current = treeMaximum(root);
      } else {
        current = predecessor(current);
      }
      return temp;
    }
    Key& operator*() const { return current->key; }
    bool operator==(const iterator& other) const {
      return current == other.current;
    }
    bool operator!=(const iterator& other) const {
      return current != other.current;
    }
  };
  // Итератор для константных объектов
  class const_iterator {
   private:
    const Node* current;
    const Node* root;
    const Node* treeMinimum(const Node* node) const;
    const Node* treeMaximum(const Node* node) const;
    const Node* successor(const Node* node) const;
    const Node* predecessor(const Node* node) const;

   public:
    const_iterator(const Node* root = nullptr, const Node* start = nullptr)
        : current(start), root(root) {}
    const_iterator& operator++() {
      current = successor(current);
      return *this;
    }
    const_iterator operator++(int) {
      const_iterator temp = *this;
      current = successor(current);
      return temp;
    }
    const_iterator& operator--() {
      if (current == nullptr) {
        current = treeMaximum(root);
      } else {
        current = predecessor(current);
      }
      return *this;
    }
    const_iterator operator--(int) {
      const_iterator temp = *this;
      if (current == nullptr) {
        current = treeMaximum(root);
      } else {
        current = predecessor(current);
      }
      return temp;
    }
    const Key& operator*() const { return current->key; }
    bool operator==(const const_iterator& other) const {
      return current == other.current;
    }
    bool operator!=(const const_iterator& other) const {
      return current != other.current;
    }
  };
  // Первый элемент, больший или равный key
  iterator lower_bound(const Key& key) {
    Node* node = root;
    Node* result = nullptr;
    while (node) {
      if (key <= node->key) {
        result = node;
        node = node->left;
      } else {
        node = node->right;
      }
    }
    return iterator(root, result);
  }
  // Первый элемент, больший key
  iterator upper_bound(const Key& key) {
    Node* node = root;
    Node* result = nullptr;
    while (node) {
      if (key < node->key) {
        result = node;
        node = node->left;
      } else {
        node = node->right;
      }
    }
    return iterator(root, result);
  }
  // Диапазон элементов с данным ключом
  std::pair<iterator, iterator> equal_range(const Key& key) {
    return {lower_bound(key), upper_bound(key)};
  }
  iterator begin() { return iterator(root, minimum(root)); }
  iterator end() { return iterator(root, nullptr); }
  const_iterator begin() const { return const_iterator(root, minimum(root)); }
  const_iterator end() const { return const_iterator(root, nullptr); }
};

#include "s21_tree.tpp"

#endif
