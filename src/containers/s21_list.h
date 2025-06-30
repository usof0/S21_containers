#ifndef S21_LIST_H
#define S21_LIST_H

#include <iostream>
#include <limits>

namespace s21 {

template <typename T>
class Node {
 public:
  Node *pNext_;
  Node *pPrev_;
  T data_;

  Node(T data = T(), Node *pNext = nullptr, Node *pPrev = nullptr) {
    this->data_ = data;
    this->pNext_ = pNext;
    this->pPrev_ = pPrev;
  }
};

template <typename T>
class List : public Node<T> {
 public:
  //  List Member type
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  class ListIterator {
    friend class List<T>;

   public:
    ListIterator();
    ListIterator(typename List<T>::Node *node);
    ListIterator(typename List<T>::Node *node,
                 typename List<T>::Node *last_node);

    reference operator*() const;
    ListIterator &operator++();
    ListIterator &operator--();
    bool operator==(const ListIterator &other) const;
    bool operator!=(const ListIterator &other) const;

   protected:
    typename List<T>::Node *node_;
    typename List<T>::Node *last_node_;
  };

  class ListConstIterator : public ListIterator {
   public:
    ListConstIterator();
    ListConstIterator(const ListIterator &node_);
    const_reference operator*() const;
  };

  using iterator = ListIterator;
  using const_iterator = ListConstIterator;

  // Constructors & destructor
  List();
  List(size_type n);
  List(std::initializer_list<value_type> const &items);
  List(const List &other);
  List(List &&other);
  ~List();

  List &operator=(List &&other);

  // Element access
  const_reference front();
  const_reference back();

  // Iterators
  iterator begin();
  iterator end();

  // Capacity
  bool empty();
  size_type size();
  size_type max_size();

  // Modifiers
  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void push_front(const_reference value);
  void pop_front();
  void swap(List &other);
  void merge(List &other);
  void splice(const_iterator pos, List &other);
  void reverse();
  void unique();
  void sort();

  // Bonus part

  template <typename... Args>
  iterator insert_many(const_iterator pos, Args &&...args);

  template <typename... Args>
  void insert_many_back(Args &&...args);

  template <typename... Args>
  void insert_many_front(Args &&...args);

 private:
  typename Node<T>::Node *head;
  typename Node<T>::Node *tail;
  size_type size_;
};

// class ListIterator

template <typename T>
List<T>::ListIterator::ListIterator(){};

template <typename T>
List<T>::ListIterator::ListIterator(typename List<T>::Node *node)
    : node_(node) {}

template <typename T>
List<T>::ListIterator::ListIterator(typename List<T>::Node *node,
                                    typename List<T>::Node *last_node)
    : node_(node), last_node_(last_node) {}

template <typename T>
typename List<T>::reference List<T>::ListIterator::operator*() const {
  return node_->data_;
}

template <typename T>
typename List<T>::ListIterator &List<T>::ListIterator::operator++() {
  last_node_ = node_;
  node_ = node_->pNext_;
  return *this;
}

template <typename T>
typename List<T>::ListIterator &List<T>::ListIterator::operator--() {
  if (node_ == nullptr) {
    node_ = last_node_;
  } else {
    node_ = node_->pPrev_;
  }
  return *this;
}

template <typename T>
bool List<T>::ListIterator::operator==(const ListIterator &other) const {
  return node_ == other.node_;
}

template <typename T>
bool List<T>::ListIterator::operator!=(const ListIterator &other) const {
  return node_ != other.node_;
}

// class ListConstIterator

template <typename T>
List<T>::ListConstIterator::ListConstIterator() : ListIterator() {}

template <typename T>
List<T>::ListConstIterator::ListConstIterator(const ListIterator &node_)
    : ListIterator(node_) {}

template <typename T>
typename List<T>::const_reference List<T>::ListConstIterator::operator*()
    const {
  return ListIterator::operator*();
}

// Constructors & destructor

template <typename T>
List<T>::List() : head(nullptr), tail(nullptr), size_(0) {}

template <typename T>
List<T>::List(size_type n) : List() {
  for (size_type i = 0; i < n; ++i) push_front(value_type());
}

template <typename T>
List<T>::List(std::initializer_list<value_type> const &items) : List() {
  for (auto i = items.begin(); i != items.end(); i++) push_back(*i);
}

template <typename T>
inline List<T>::List(const List &other) : List<T>::List() {
  typename Node<T>::Node *p = other.head;
  while (p != nullptr) {
    this->push_back(p->data_);
    p = p->pNext_;
  }
}

template <typename T>
inline List<T>::List(List &&other)
    : head(other.head), tail(other.tail), size_(other.size_) {
  other.head = nullptr;
  other.tail = nullptr;
  other.size_ = 0;
}

template <typename T>
List<T>::~List() {
  clear();
}

template <typename T>
typename List<T>::List &List<T>::operator=(List &&other) {
  if (this != &other) {
    clear();
    this->head = other.head;
    this->tail = other.tail;
    size_ = other.size_;
    other.head = nullptr;
    other.tail = nullptr;
    other.size_ = 0;
  }
  return *this;
}

// Element access

template <typename T>
typename List<T>::const_reference List<T>::front() {
  return this->head->data_;
}

template <typename T>
typename List<T>::const_reference List<T>::back() {
  return this->tail->data_;
}

// Iterators

template <typename T>
typename List<T>::iterator List<T>::begin() {
  return iterator(this->head);
}

template <typename T>
typename List<T>::iterator List<T>::end() {
  return this->head ? iterator(this->tail->pNext_, this->tail) : begin();
}

// Capacity

template <typename T>
bool List<T>::empty() {
  return size_ == 0;
}

template <typename T>
typename List<T>::size_type List<T>::size() {
  return size_;
}

template <typename T>
typename List<T>::size_type List<T>::max_size() {
  return std::numeric_limits<size_type>::max() /
         sizeof(typename List<T>::Node) / 2;
}

// Modifiers

template <typename T>
void List<T>::clear() {
  while (head) {
    Node<T> *temp = head;
    head = head->pNext_;
    delete temp;
  }
  tail = nullptr;
  size_ = 0;
}

template <typename T>
typename List<T>::iterator List<T>::insert(iterator pos,
                                           const_reference value) {
  if (pos == this->begin()) {
    push_front(value);
    pos = this->head;
  } else if (pos == this->end()) {
    push_back(value);
    pos = this->tail;
  } else {
    typename Node<T>::Node *current = pos.node_;
    typename Node<T>::Node *blank =
        new typename Node<T>::Node(value, current, current->pPrev_);
    current->pPrev_->pNext_ = blank;
    current->pPrev_ = blank;
    this->size_++;
    pos = iterator(blank);
  }
  return pos;
}

template <typename T>
void List<T>::erase(iterator pos) {
  Node<T> *current = pos.node_;

  if (current) {
    if (current->pPrev_) {
      current->pPrev_->pNext_ = current->pNext_;
    } else {
      head = current->pNext_;
    }

    if (current->pNext_) {
      current->pNext_->pPrev_ = current->pPrev_;
    } else {
      tail = current->pPrev_;
    }

    delete current;
    --size_;
  }
}

template <typename T>
void List<T>::push_back(const_reference value) {
  Node<T> *new_node = new Node<T>(value, nullptr, tail);
  if (tail) {
    tail->pNext_ = new_node;
  } else {
    head = new_node;
  }
  tail = new_node;
  ++size_;
}

template <typename T>
void List<T>::pop_back() {
  if (tail) {
    Node<T> *old_tail = tail;
    tail = tail->pPrev_;
    if (tail) {
      tail->pNext_ = nullptr;
    } else {
      head = nullptr;
    }
    delete old_tail;
    --size_;
  }
}

template <typename T>
void List<T>::push_front(const_reference value) {
  Node<T> *new_node = new Node<T>(value, head, nullptr);
  if (head) {
    head->pPrev_ = new_node;
  } else {
    tail = new_node;
  }
  head = new_node;
  ++size_;
}

template <typename T>
void List<T>::pop_front() {
  if (head) {
    Node<T> *old_head = head;
    head = head->pNext_;
    if (head) {
      head->pPrev_ = nullptr;
    } else {
      tail = nullptr;
    }
    delete old_head;
    --size_;
  }
}

template <typename T>
void List<T>::swap(List &other) {
  std::swap(head, other.head);
  std::swap(tail, other.tail);
  std::swap(size_, other.size_);
}

template <typename T>
void List<T>::merge(List &other) {
  if (this != &other) {
    typename Node<T>::Node *p = other.head;
    while (p != nullptr) {
      this->push_back(p->data_);
      other.pop_front();
      p = other.head;
    }
  }
}

template <typename T>
void List<T>::splice(List<T>::const_iterator pos, List &other) {
  if (!other.empty()) {
    for (iterator it_other = other.begin(); it_other != other.end();
         ++it_other) {
      insert(pos, *it_other);
    }
  }
}

template <typename T>
void List<T>::reverse() {
  Node<T> *current = head;
  Node<T> *temp = nullptr;

  while (current != nullptr) {
    temp = current->pNext_;
    current->pNext_ = current->pPrev_;
    if (temp != nullptr) {
      current->pPrev_ = temp;
      current = temp;
    } else {
      current->pPrev_ = nullptr;
      current = nullptr;
    }
  }

  std::swap(head, tail);
}

template <typename T>
void List<T>::unique() {
  if (head == nullptr) return;

  Node<T> *current = head;
  while (current->pNext_ != nullptr) {
    if (current->data_ == current->pNext_->data_) {
      Node<T> *temp = current->pNext_;
      current->pNext_ = temp->pNext_;
      if (current->pNext_ != nullptr) {
        current->pNext_->pPrev_ = current;
      } else {
        tail = current;
      }
      delete temp;
      --size_;
    } else {
      current = current->pNext_;
    }
  }
}

template <typename T>
void List<T>::sort() {
  if (size_ < 2) return;

  bool swapped;
  do {
    swapped = false;
    Node<T> *current = head;

    while (current != nullptr && current->pNext_ != nullptr) {
      if (current->data_ > current->pNext_->data_) {
        std::swap(current->data_, current->pNext_->data_);
        swapped = true;
      }
      current = current->pNext_;
    }
  } while (swapped);
}

// Bonus part

template <typename T>
template <typename... Args>
typename List<T>::iterator List<T>::insert_many(List<T>::const_iterator pos,
                                                Args &&...args) {
  for (const auto &arg : {args...}) {
    insert(pos, arg);
  }
  return pos;
}

template <typename T>
template <typename... Args>
inline void List<T>::insert_many_back(Args &&...args) {
  const_iterator pos = this->end();
  for (const auto &arg : {args...}) {
    insert(pos, arg);
  }
}

template <typename T>
template <typename... Args>
void List<T>::insert_many_front(Args &&...args) {
  for (const auto &arg : {args...}) {
    const_iterator pos = this->begin();
    insert(pos, arg);
  }
}

}  // namespace s21

#endif
