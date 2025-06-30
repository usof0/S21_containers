#ifndef S21_CONTAINERS_H
#define S21_CONTAINERS_H

namespace s21 {
template <typename T>
constexpr T &&move(T &obj) noexcept {
  return static_cast<T &&>(obj);
}

}  // namespace s21

#include "containers/Map/s21_map.h"
#include "containers/Multiset/s21_multiset.h"
#include "containers/Set/s21_set.h"
#include "containers/Tree/s21_tree.h"
#include "containers/s21_array.h"
#include "containers/s21_list.h"
#include "containers/s21_queue.h"
#include "containers/s21_stack.h"
#include "containers/s21_vector.h"

#endif
