#ifndef S21_SET_TPP
#define S21_SET_TPP

#include "s21_set.h"

namespace s21 {
// Конструкторы
template <typename Key>
set<Key>::set() : RBTree<Key, Key>() {}

template <typename Key>
set<Key>::set(std::initializer_list<value_type> const& items)
    : RBTree<Key, Key>() {
  for (const auto& item : items) {
    this->insert(item);
  }
}

template <typename Key>
set<Key>::set(const set& s) : RBTree<Key, Key>(s) {}

template <typename Key>
set<Key>::set(set&& s) noexcept : RBTree<Key, Key>(s21::move(s)) {}

// Перегрузки оператора присвоения
template <typename Key>
set<Key>& set<Key>::operator=(set&& s) noexcept {
  if (this != &s) {
    RBTree<Key, Key>::operator=(s21::move(s));
  }
  return *this;
}

template <typename Key>
set<Key>& set<Key>::operator=(const set& s) {
  if (this != &s) {
    RBTree<Key, Key>::operator=(s);
  }
  return *this;
}

// Очистка памяти при удалении ключа
template <typename Key>
void set<Key>::clear() {
  RBTree<Key, Key>::clear(RBTree<Key, Key>::root);
  RBTree<Key, Key>::root = nullptr;
  RBTree<Key, Key>::node_count = 0;
}

// Вставка нового элемента
template <typename Key>
std::pair<typename set<Key>::iterator, bool> set<Key>::insert(
    const value_type& value) {
  auto result = RBTree<Key, Key>::insert(value, value);
  return std::make_pair(iterator(RBTree<Key, Key>::root, result.first),
                        result.second);
}

// Удаление ключа по итератору
template <typename Key>
void set<Key>::erase(iterator pos) {
  if (pos != this->end()) {
    RBTree<Key, Key>::erase(*pos);
  }
}

// Обмен содержимым между узлами
template <typename Key>
void set<Key>::swap(set& other) {
  std::swap(RBTree<Key, Key>::root, other.root);
  std::swap(RBTree<Key, Key>::node_count, other.node_count);
}

// Слияние узлов
template <typename Key>
void set<Key>::merge(set& other) {
  for (auto it = other.begin(); it != other.end(); ++it) {
    this->insert(*it);
  }
  other.clear();
}

// Поиск узла по ключу
template <typename Key>
typename set<Key>::iterator set<Key>::find(const key_type& key) {
  return iterator(RBTree<Key, Key>::root, RBTree<Key, Key>::findNode(key));
}

template <typename Key>
typename set<Key>::const_iterator set<Key>::find(const key_type& key) const {
  return const_iterator(RBTree<Key, Key>::root,
                        RBTree<Key, Key>::findNode(key));
}

// Вставка множества элементов
template <typename Key>
template <typename... Args>  // Параметрическая упаковка. Args — список типов
                             // аргументов
std::vector<std::pair<typename set<Key>::iterator, bool>> set<Key>::insert_many(
    Args&&... args) {
  std::vector<std::pair<iterator, bool>> result;
  (result.push_back(this->insert(std::forward<Args>(args))),
   ...);  // Fold expression (свёртка выражений)
  return result;
}
}  // namespace s21

#endif  // S21_SET_TPP
