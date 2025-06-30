#ifndef S21_VECTOR_H
#define S21_VECTOR_H

#include <iostream>
#include <limits>

namespace s21 {
template <typename T>
class vector {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

  vector() noexcept;
  vector(size_type n);
  vector(const std::initializer_list<value_type> &items);
  vector(const vector &other);
  vector(vector &&other) noexcept;
  ~vector();
  vector &operator=(vector &&other) noexcept;

  reference at(size_type pos);
  reference operator[](size_type pos);
  const_reference front() const;
  const_reference back() const;
  T *data() noexcept { return data_; }

  iterator begin();
  iterator end();

  bool empty() const;
  size_type size() const;
  size_type max_size();
  void reserve(size_type size);
  size_type capacity();
  void shrink_to_fit();

  void clear() noexcept;
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void swap(vector &other);

  // insert many
  template <typename... Args>
  iterator insert_many(const_iterator pos, Args &&...args);
  template <typename... Args>
  void insert_many_back(Args &&...args);

 private:
  size_type size_;
  size_type capacity_;
  T *data_;
};

template <typename T>
inline vector<T>::vector() noexcept : size_(0), capacity_(0), data_(nullptr) {}

template <typename T>
inline vector<T>::vector(size_type n) : size_(n), capacity_(n), data_(nullptr) {
  if (size_ > 0) {
    data_ = new value_type[size_];
  }
}

template <typename T>
inline vector<T>::vector(const std::initializer_list<value_type> &items)
    : size_(0), capacity_(0), data_(nullptr) {
  for (const value_type &i : items) {
    push_back(i);
  }
}

template <typename T>
inline vector<T>::vector(const vector &other)
    : size_(other.size_), capacity_(other.capacity_) {
  data_ = new value_type[capacity_];
  for (size_t i = 0; i < size_; i++) {
    data_[i] = other.data_[i];
  }
}

template <typename T>
inline vector<T>::vector(vector &&other) noexcept
    : size_(0), capacity_(0), data_(nullptr) {
  *this = s21::move(other);
}

template <typename T>
inline vector<T>::~vector() {
  delete[] data_;
}

template <typename T>
inline vector<T> &vector<T>::operator=(vector &&other) noexcept {
  if (this != &other) {
    delete[] data_;
    data_ = other.data_;
    size_ = other.size_;
    capacity_ = other.capacity_;

    other.data_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
  }
  return *this;
}

template <typename T>
inline typename vector<T>::reference vector<T>::at(size_type pos) {
  if (pos >= size_) {
    throw std::out_of_range("Index out of range in vector::at");
  }
  return data_[pos];
}

template <typename T>
inline typename vector<T>::reference vector<T>::operator[](size_type pos) {
  return data_[pos];
}

template <typename T>
inline typename vector<T>::const_reference vector<T>::front() const {
  if (empty()) {
    throw std::logic_error("Vector is empty!");
  }
  return data_[0];
}

template <typename T>
inline typename vector<T>::const_reference vector<T>::back() const {
  if (empty()) {
    throw std::logic_error("Vector is empty!");
  }
  return data_[size_ - 1];
}

template <typename T>
inline typename vector<T>::iterator vector<T>::begin() {
  return data_;
}

template <typename T>
inline typename vector<T>::iterator vector<T>::end() {
  return data_ + size_;
}

template <typename T>
inline bool vector<T>::empty() const {
  return size_ == 0;
}

template <typename T>
inline typename vector<T>::size_type vector<T>::size() const {
  return size_;
}

template <typename T>
inline typename vector<T>::size_type vector<T>::max_size() {
  return std::numeric_limits<size_type>::max() / sizeof(T) / 2;
}

template <typename T>
inline void vector<T>::reserve(size_type size) {
  if (size > capacity_) {
    value_type *new_data = new value_type[size];
    for (size_type i = 0; i < size_; i++) {
      new_data[i] = data_[i];
    }
    data_ = nullptr;
    data_ = new_data;
    capacity_ = size;
  }
}

template <typename T>
inline typename vector<T>::size_type vector<T>::capacity() {
  return capacity_;
}

template <typename T>
inline void vector<T>::shrink_to_fit() {
  if (capacity_ > size_) {
    value_type *new_data = new value_type[size_];
    for (size_type i = 0; i < size_; i++) {
      new_data[i] = data_[i];
    }
    delete[] data_;
    data_ = new_data;
    capacity_ = size_;
  }
}

template <typename T>
inline void vector<T>::clear() noexcept {
  if (capacity_ > 0) {
    delete[] data_;
    data_ = nullptr;
  }
  size_ = 0;
  capacity_ = 0;
}

template <typename T>
inline typename vector<T>::iterator vector<T>::insert(iterator pos,
                                                      const_reference value) {
  size_type index = pos - begin();
  if (size_ == capacity_)
    reserve(capacity_ + (index > capacity_ ? (index - capacity_) : 1));
  for (size_type i = size_; i > index; --i) {
    data_[i] = data_[i - 1];
  }
  data_[index] = value;
  ++size_;
  return begin() + index;
}

template <typename T>
inline void vector<T>::erase(iterator pos) {
  if (pos > end() || pos < begin()) throw std::out_of_range("out of range!");
  if (pos >= begin() && pos < end()) {
    for (auto i = pos; i != end() - 1; ++i) {
      *i = *(i + 1);
    }
  }
  --size_;
}

template <typename T>
inline void vector<T>::push_back(const_reference value) {
  if (size_ == capacity_) {
    reserve(capacity_ + 1);
  }
  data_[size_] = value;
  ++size_;
}

template <typename T>
inline void vector<T>::pop_back() {
  if (size() == 0) {
    throw std::out_of_range("Cannot pop from an empty vector");
  }
  --size_;
}

template <typename T>
inline void vector<T>::swap(vector &other) {
  if (this != &other) {
    value_type *temp_data = data_;
    size_type temp_size = size_;
    size_type temp_capacity = capacity_;

    data_ = other.data_;
    size_ = other.size_;
    capacity_ = other.capacity_;

    other.data_ = temp_data;
    other.size_ = temp_size;
    other.capacity_ = temp_capacity;
  }
}

template <typename T>
template <typename... Args>
inline typename vector<T>::iterator vector<T>::insert_many(const_iterator pos,
                                                           Args &&...args) {
  size_type index = pos - begin();
  size_type num_new_elements = sizeof...(args);

  if (size_ + num_new_elements > capacity_) {
    reserve(capacity_ + (index > capacity_ ? (index - capacity_) : 0) +
            num_new_elements);
  }

  for (size_type i = size_; i > index; --i) {
    data_[i + num_new_elements - 1] = s21::move(data_[i - 1]);
  }

  size_type offset = 0;
  ((data_[index + offset++] = std::forward<Args>(args)), ...);

  size_ += num_new_elements;
  return begin() + index;
}

template <typename T>
template <typename... Args>
inline void vector<T>::insert_many_back(Args &&...args) {
  size_type num_new_elements = sizeof...(args);

  if (size_ + num_new_elements > capacity_) {
    reserve(size_ + num_new_elements);
  }

  ((data_[size_++] = std::forward<Args>(args)), ...);
}

}  // namespace s21

#endif
