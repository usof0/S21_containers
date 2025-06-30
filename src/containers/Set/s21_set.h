#ifndef S21_SET_H
#define S21_SET_H

#include <initializer_list>
#include <limits>
#include <vector>

#include "../Tree/s21_tree.h"

namespace s21 {
template <typename Key>
class set : public RBTree<Key, Key> {
 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = typename RBTree<Key, Key>::iterator;
  using const_iterator = typename RBTree<Key, Key>::const_iterator;
  using size_type = size_t;

  // Конструкторы и деструктор
  set();
  set(std::initializer_list<value_type> const& items);
  set(const set& s);
  set(set&& s) noexcept;
  ~set() = default;

  // Перегрузки операторов
  set& operator=(set&& s) noexcept;
  set& operator=(const set& s);

  // Методы класса
  bool empty() const { return RBTree<Key, Key>::size() == 0; }
  size_type size() const { return RBTree<Key, Key>::size(); }
  size_type max_size() const { return std::numeric_limits<size_type>::max(); }
  void clear();
  std::pair<iterator, bool> insert(const value_type& value);
  void erase(iterator pos);
  void swap(set& other);
  void merge(set& other);
  iterator find(const key_type& key);
  const_iterator find(const key_type& key) const;
  bool contains(const key_type& key) const {
    return RBTree<Key, Key>::contains(key);
  }
  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args&&... args);
};
}  // namespace s21

#include "s21_set.tpp"

#endif  // S21_SET_H
