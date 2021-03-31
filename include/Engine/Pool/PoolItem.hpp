#pragma once

#include <type_traits>

#include <Engine/Common/Log.hpp>

/**
 * @brief Les PoolItem stockent chaque élément d'une arène
 */
template <typename T> class PoolItem {
public:
  // Methods for the list of free items.
  PoolItem<T> *get_next_item() const { return next; }
  void set_next_item(PoolItem<T> *n) { next = n; }

  // Methods for the storage of the item.
  T *get_storage() { return reinterpret_cast<T *>(&datum); }

  // Given a T* cast it to a PoolItem*
  static PoolItem<T> *storage_to_item(T *t) {
    PoolItem *current_item = reinterpret_cast<PoolItem<T> *>(t);
    return current_item;
  }

  bool is_set = false;
  
private:
  using StorageType = typename std::aligned_storage<sizeof(T), alignof(T)>::type;

  // Points to the next freely available item.
  PoolItem<T> *next;
  // Storage of the item. Note that this is a union
  // so it is shared with the pointer "next" above.
  StorageType datum;
};