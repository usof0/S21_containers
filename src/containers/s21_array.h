#ifndef S21_ARRAY_H
#define S21_ARRAY_H

#include <iostream>

namespace s21 {

template <typename T, size_t N>
class array {
 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using iterator = T*;
  using const_iterator = const T*;
  using size_type = size_t;

 private:
  value_type data_[N];

 public:
  array() = default;
  array(const std::initializer_list<value_type>& items);
  array(const array& ather);
  array(array&& other) noexcept;
  ~array() = default;

  array& operator=(array&& other) noexcept;

  reference at(size_type pos);
  reference operator[](size_type pos);
  const_reference front() const;
  const_reference back() const;
  iterator data();

  iterator begin();
  iterator end();

  bool empty() const;
  size_type size() const;
  size_type max_size() const;

  void swap(array& other);
  void fill(const_reference value);
};

template <typename T, size_t N>
inline array<T, N>::array(const std::initializer_list<value_type>& items) {
  size_type i = 0;
  for (const auto& item : items) {
    if (i < N) {
      data_[i++] = item;
    } else {
      break;
    }
  }
}

template <typename T, size_t N>
inline array<T, N>::array(const array& other) {
  for (size_type i = 0; i < N; ++i) {
    data_[i] = other.data_[i];
  }
}

template <typename T, size_t N>
inline array<T, N>::array(array&& other) noexcept {
  *this = s21::move(other);
}

template <typename T, size_t N>
inline array<T, N>& array<T, N>::operator=(array&& other) noexcept {
  if (this != &other) {
    for (size_type i = 0; i < N; ++i) {
      data_[i] = s21::move(other.data_[i]);
    }
  }
  return *this;
}

template <typename T, size_t N>
inline typename array<T, N>::reference array<T, N>::at(size_type pos) {
  if (pos >= N) throw std::out_of_range("index out of range");
  return data_[pos];
}

template <typename T, size_t N>
inline typename array<T, N>::reference array<T, N>::operator[](size_type pos) {
  return data_[pos];
}

template <typename T, size_t N>
inline typename array<T, N>::const_reference array<T, N>::front() const {
  return data_[0];
}

template <typename T, size_t N>
inline typename array<T, N>::const_reference array<T, N>::back() const {
  return data_[N - 1];
}

template <typename T, size_t N>
inline typename array<T, N>::iterator array<T, N>::data() {
  return data_;
}

template <typename T, size_t N>
inline typename array<T, N>::iterator array<T, N>::begin() {
  return data_;
}

template <typename T, size_t N>
inline typename array<T, N>::iterator array<T, N>::end() {
  return data_ + N;
}

template <typename T, size_t N>
inline bool array<T, N>::empty() const {
  return N == 0;
}

template <typename T, size_t N>
inline typename array<T, N>::size_type array<T, N>::size() const {
  return N;
}

template <typename T, size_t N>
inline typename array<T, N>::size_type array<T, N>::max_size() const {
  return N;
}

template <typename T, size_t N>
inline void array<T, N>::swap(array& other) {
  for (size_type i = 0; i < N; ++i) {
    value_type temp = data_[i];
    data_[i] = other.data_[i];
    other.data_[i] = temp;
  }
}

template <typename T, size_t N>
inline void array<T, N>::fill(const_reference value) {
  for (size_type i = 0; i < N; ++i) {
    data_[i] = value;
  }
}

}  // namespace s21

#endif
