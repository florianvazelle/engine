#pragma once

#include <iostream>
#include <type_traits>

#include <Engine/Common/Entity.hpp>
#include <Engine/Common/Log.hpp>
#include <Engine/IPool.hpp>

/**
 * @brief Une Pool alloue des objets pour une utilisation ultérieure
 */
template <typename T> class Pool {
public:
  /**
   * @brief Les PoolItem stockent chaque élément d'une arène
   * On définie un union pour partager l'espace
   */
  union PoolItem {
  public:
    // Methods for the list of free items.
    PoolItem *get_next_item() const { return next; }
    void set_next_item(PoolItem *n) { next = n; }

    // Methods for the storage of the item.
    T *get_storage() { return reinterpret_cast<T *>(&datum); }

    // Given a T* cast it to a PoolItem*
    static PoolItem *storage_to_item(T *t) {
      PoolItem *current_item = reinterpret_cast<PoolItem *>(t);
      return current_item;
    }

  private:
    using StorageType = typename std::aligned_storage<sizeof(T), alignof(T)>::type;

    // Points to the next freely available item.
    PoolItem *next;

    // Storage of the item. Note that this is a union
    // so it is shared with the pointer "next" above.
    StorageType datum;
  };

  class Arena {
  public:
    /**
     * @brief Le constructeur alloue un table de PoolItem, de taille arena_size
     */
    Arena(size_t arena_size) : storage(new PoolItem[arena_size]) {
      if (arena_size <= 0) {
        throw std::invalid_argument("Arena size must be positive");
      }

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
    PoolItem *get_storage() const { return storage.get(); }

  private:
    std::unique_ptr<PoolItem[]> storage;  // Storage of this arena.
  };

  /**
   * @brief Crée une nouvelle Pool qui utilisera des Arena de arena_size
   */
  Pool(size_t arena_size) : arena_size(arena_size), arena(new Arena(arena_size)), free_list(arena->get_storage()) {}

  /**
   * @brief Au moment de la destruction de la Pool, on va libéré toute les valeurs qui y sont stocké
   */
  ~Pool() {
    PoolItem *s = arena->get_storage();
    for (int i = 0; i < arena_size; ++i) {
      free((s + i)->get_storage());
    }
  }

  /**
   * @brief Alloue un objet dans l'arène
   * @return Pointeur vers l'objet alloué
   */
  template <typename... Args> T *alloc(Args &&... args) {
    assert(free_list != nullptr && "Unable to get more object from the pool, Arena is full.");

    // Get the first free item.
    PoolItem *current_item = free_list;
    // Update the free list to the next free item.
    free_list = current_item->get_next_item();

    return set_storage(current_item, std::forward<Args>(args)...);
  }

  /**
   * @brief Libère un objet dans l'arène
   */
  void free(T *t) {
    // Destroy the object.
    t->T::~T();

    // Convert this pointer to T to its enclosing pointer of an item of the
    // arena.
    PoolItem *current_item = PoolItem::storage_to_item(t);

    // Add the item at the beginning of the free list.
    current_item->set_next_item(free_list);
    free_list = current_item;
  }

  typedef PoolItem *iterator;

  iterator begin() {
    PoolItem *current_item = arena->get_storage();
    if (in_free_list(current_item)) return next(current_item);
    return current_item;
  }

  iterator end() { return begin() + arena_size; }

  // TODO : we can override operator++
  iterator next(iterator item) {
    PoolItem *current_item = item->get_next_item();
    if (current_item == nullptr) return end();

    while (in_free_list(current_item)) {
      current_item = current_item->get_next_item();
      if (current_item == nullptr) return end();
    }

    return current_item;
  }

  PoolItem *at(const uint32_t &id) {
    assert(id < arena_size && "Pool out of range.");
    return arena->get_storage() + id;
  }

  PoolItem *at(const uint32_t &id) const { return this->at(id); }

private:
  // Size of the arenas created by the pool.
  size_t arena_size;

  // Current arena. Changes when it becomes full and we want to allocate one
  // more object.
  std::unique_ptr<Arena> arena;

  // List of free elements. The list can be threaded between different arenas
  // depending on the deallocation pattern.
  PoolItem *free_list;

  template <typename... Args> T *set_storage(PoolItem *current_item, Args &&... args) {
    // Get the storage for T.
    T *result = current_item->get_storage();

    // Construct the object in the obtained storage.
    new (result) T(std::forward<Args>(args)...);

    return result;
  }
};