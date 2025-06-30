#ifndef S21_STACK_H
#define S21_STACK_H

#include <iostream>

namespace s21 {
template <typename T>
class stack {
 private:
  class Node_ {
   public:
    T data_;
    Node_ *next_;

    Node_(const T &value = T(), Node_ *next = nullptr)
        : data_(value), next_(next) {}
  };

  Node_ *head_;
  size_t size_;

 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  // constructors & destructor
  stack() noexcept;
  stack(const std::initializer_list<value_type> &items) noexcept;
  stack(const stack &other);
  stack(stack &&other) noexcept;
  ~stack();

  stack &operator=(const stack &other) noexcept;
  stack &operator=(stack &&other) noexcept;

  const_reference top() const;
  bool empty() const;
  size_type size() const;
  void push(const_reference value);
  void pop();
  void swap(stack &other);

  void clear();

  // insert many back (push many)
  template <typename... Args>
  void insert_many_back(Args &&...args);

  // get_head() function can be used to loop through the stack items from
  // outside the library
  Node_ *get_head() const;
};

template <typename T>
inline stack<T>::stack() noexcept : head_(nullptr), size_(0) {}

template <typename T>
inline stack<T>::stack(const std::initializer_list<value_type> &items) noexcept
    : head_(nullptr), size_(0) {
  for (value_type i : items) {
    push(i);
  }
}

template <typename T>
inline stack<T>::stack(const stack<T> &other) : head_(nullptr), size_(0) {
  *this = other;
}

template <typename T>
inline stack<T>::stack(stack<T> &&other) noexcept : head_(nullptr), size_(0) {
  *this = s21::move(other);
}

template <typename T>
inline stack<T>::~stack() {
  clear();
}

template <typename T>
inline stack<T> &stack<T>::operator=(const stack<T> &other) noexcept {
  if (this != &other) {
    clear();
    stack<T> temp_stack;
    auto temp_head = other.get_head();
    while (temp_head != nullptr) {
      temp_stack.push(temp_head->data_);
      temp_head = temp_head->next_;
    }
    temp_head = temp_stack.get_head();
    while (temp_head != nullptr) {
      push(temp_head->data_);
      temp_head = temp_head->next_;
    }
    temp_stack.clear();
  }
  return *this;
}

template <typename T>
inline stack<T> &stack<T>::operator=(stack<T> &&other) noexcept {
  if (this != &other) {
    clear();
    head_ = other.head_;
    size_ = other.size_;
    other.head_ = nullptr;
    other.size_ = 0;
  }
  return *this;
}

template <typename T>
inline typename stack<T>::const_reference stack<T>::top() const {
  if (!head_) throw std::logic_error("stack is empty!");
  return head_->data_;
}

template <typename T>
inline bool stack<T>::empty() const {
  return size_ == 0;
}

template <typename T>
inline typename stack<T>::size_type stack<T>::size() const {
  return size_;
}

template <typename T>
inline void stack<T>::push(const_reference value) {
  Node_ *new_node = new Node_(value);
  if (!head_) {
    head_ = new_node;
  } else {
    new_node->next_ = head_;
    head_ = new_node;
  }
  ++size_;
}

template <typename T>
inline void stack<T>::pop() {
  if (!head_) throw std::logic_error("stack is empty!");
  Node_ *old_head = head_;
  head_ = head_->next_;
  delete old_head;
  --size_;
}

template <typename T>
inline void stack<T>::swap(stack<T> &other) {
  if (this != &other) {
    Node_ *temp = head_;
    head_ = other.head_;
    other.head_ = temp;

    size_type temp_size = size_;
    size_ = other.size_;
    other.size_ = temp_size;
  }
}

template <typename T>
inline void stack<T>::clear() {
  while (head_) pop();
}

template <typename T>
inline typename stack<T>::Node_ *stack<T>::get_head() const {
  return head_;
}

template <typename T>
template <typename... Args>
inline void stack<T>::insert_many_back(Args &&...args) {
  (push(std::forward<Args>(args)), ...);
}

}  // namespace s21

#endif
