#ifndef S21_QUEUE_H
#define S21_QUEUE_H

#include <iostream>

namespace s21 {
template <typename T>
class queue {
 private:
  class Node_ {
   public:
    T data_;
    Node_ *next_;

    Node_(const T &value = T(), Node_ *next = nullptr)
        : data_(value), next_(next) {}
  };

  Node_ *head_;
  Node_ *tail_;
  size_t size_;

 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  // constructors & destructor
  queue() : head_(nullptr), tail_(nullptr), size_(0) {}
  queue(const std::initializer_list<value_type> &items);
  queue(const queue &other);
  queue(queue &&other) noexcept;
  ~queue();

  queue &operator=(const queue &other) noexcept;
  queue &operator=(queue &&other) noexcept;

  const_reference front() const;
  const_reference back() const;
  bool empty() const;
  size_type size() const;
  void push(const_reference value);
  void pop();
  void swap(queue &other);

  void clear();
  // insert many back (push many)
  template <typename... Args>
  void insert_many_back(Args &&...args);

  // get_head() function can be used to loop through the queue items from
  // outside the library
  Node_ *get_head() const;
};

template <typename T>
inline queue<T>::queue(const std::initializer_list<value_type> &items)
    : head_(nullptr), tail_(nullptr), size_(0) {
  for (const value_type i : items) {
    push(i);
  }
}

template <typename T>
inline queue<T>::queue(const queue<T> &other)
    : head_(nullptr), tail_(nullptr), size_(0) {
  Node_ *temp = other.head_;
  while (temp != nullptr) {
    push(temp->data_);
    temp = temp->next_;
  }
}

template <typename T>
inline queue<T>::queue(queue<T> &&other) noexcept
    : head_(nullptr), tail_(nullptr), size_(0) {
  *this = s21::move(other);
}

template <typename T>
inline queue<T>::~queue() {
  clear();
}

template <typename T>
inline queue<T> &queue<T>::operator=(const queue<T> &other) noexcept {
  if (this != &other) {
    clear();
    queue<T> temp_queue;
    auto temp_head = other.get_head();
    while (temp_head != nullptr) {
      temp_queue.push(temp_head->data_);
      temp_head = temp_head->next_;
    }

    temp_head = temp_queue.get_head();
    while (temp_head != nullptr) {
      push(temp_head->data_);
      temp_head = temp_head->next_;
    }
    temp_queue.clear();
  }
  return *this;
}

template <typename T>
inline queue<T> &queue<T>::operator=(queue<T> &&other) noexcept {
  if (this != &other) {
    clear();
    head_ = other.head_;
    tail_ = other.tail_;
    size_ = other.size_;
    other.head_ = nullptr;
    other.tail_ = nullptr;
    other.size_ = 0;
  }
  return *this;
}

template <typename T>
inline typename queue<T>::const_reference queue<T>::front() const {
  if (!head_) throw std::logic_error("queue is empty!");
  return head_->data_;
}

template <typename T>
inline typename queue<T>::const_reference queue<T>::back() const {
  if (!head_) throw std::logic_error("queue is empty!");
  return tail_->data_;
}

template <typename T>
inline bool queue<T>::empty() const {
  return size_ == 0;
}

template <typename T>
inline typename queue<T>::size_type queue<T>::size() const {
  return size_;
}

template <typename T>
inline void queue<T>::push(const_reference value) {
  Node_ *new_node = new Node_(value);
  if (tail_) {
    tail_->next_ = new_node;
  } else {
    head_ = new_node;
  }
  tail_ = new_node;
  ++size_;
}

template <typename T>
inline void queue<T>::pop() {
  if (!head_) throw std::logic_error("queue is empty!");
  Node_ *old_head = head_;
  head_ = head_->next_;
  delete old_head;
  --size_;
  if (!head_) tail_ = nullptr;
}

template <typename T>
inline void queue<T>::swap(queue<T> &other) {
  if (this != &other) {
    Node_ *temp_head = head_;
    head_ = other.head_;
    other.head_ = temp_head;

    Node_ *temp_tail = tail_;
    tail_ = other.tail_;
    other.tail_ = temp_tail;

    size_t temp_size = size_;
    size_ = other.size_;
    other.size_ = temp_size;
  }
}

template <typename T>
inline void queue<T>::clear() {
  while (head_) pop();
}

template <typename T>
inline typename queue<T>::Node_ *queue<T>::get_head() const {
  return head_;
}

template <typename T>
template <typename... Args>
inline void queue<T>::insert_many_back(Args &&...args) {
  (push(std::forward<Args>(args)), ...);
}

}  // namespace s21

#endif
