#pragma once

#include <memory>

#include <Engine/Pool/PoolItem.hpp>

template <typename T> class Arena {
public:
  /**
   * @brief Le constructeur alloue un table de PoolItem, de taille arena_size
   */
  Arena(size_t arena_size) : storage(new PoolItem<T>[arena_size]) {
    for (size_t i = 1; i < arena_size; i++) {
      // Set the "next" pointer of each item
      storage[i - 1].set_next_item(&storage[i]);
    }
    // Last "next" pointer of the storage is null
    storage[arena_size - 1].set_next_item(nullptr);
  }

  // Returns a pointer to the array of items. This is used by the arena
  // itself. This is only used to update free_list during initialization
  // or when creating a new arena when the current one is full.
  PoolItem<T> *get_storage() const { return storage.get(); }

private:
  std::unique_ptr<PoolItem<T>[]> storage;  // Storage of this arena.
  std::unique_ptr<Arena<T>> next;          // Pointer to the next arena.
};