#pragma once

#include <Engine/Pool/Arena.hpp>
#include <Engine/Pool/PoolItem.hpp>

/**
 * @brief Une Pool alloue des objets pour une utilisation ultérieure
 */
template <typename T> class Pool {
public:
  /**
   * @brief Crée une nouvelle Pool qui utilisera des Arena de arena_size
   */
  Pool(size_t arena_size) : arena_size(arena_size), arena(new Arena<T>(arena_size)), free_list(arena->get_storage()) {}

  /**
   * @brief Au moment de la destruction de la Pool, on va libéré toute les valeurs qui y sont stocké
   */
  ~Pool() {
    PoolItem<T> *s = arena->get_storage();
    for (int i = 0; i < arena_size; ++i) {
      free((s + i)->get_storage());
    }
  }

  /**
   * @brief Alloue un objet dans l'arène
   * @return Pointeur vers l'objet alloué
   */
  template <typename... Args> T *alloc(Args &&... args) {
    if (free_list == nullptr) {
      std::cout << "Unable to get more object from the pool, Arena is full" << std::endl;
      return nullptr;
    }

    // Get the first free item.
    PoolItem<T> *current_item = free_list;
    // Update the free list to the next free item.
    free_list = current_item->get_next_item();

    // Get the storage for T.
    T *result = current_item->get_storage();
    // Construct the object in the obtained storage.
    new (result) T(std::forward<Args>(args)...);

    return result;
  }

  /**
   * @brief Libère un objet dans l'arène
   */
  void free(T *t) {
    // Destroy the object.
    t->T::~T();

    // Convert this pointer to T to its enclosing pointer of an item of the
    // arena.
    PoolItem<T> *current_item = PoolItem<T>::storage_to_item(t);

    // Add the item at the beginning of the free list.
    current_item->set_next_item(free_list);
    free_list = current_item;
  }

  typedef T *iterator;
  typedef const T *const_iterator;

  iterator begin() { return arena->get_storage()->get_storage(); }
  const_iterator begin() const { return begin(); }

  iterator end() { return begin() + arena_size; }
  const_iterator end() const { return end(); }

private:
  // Size of the arenas created by the pool.
  size_t arena_size;
  // Current arena. Changes when it becomes full and we want to allocate one
  // more object.
  std::unique_ptr<Arena<T>> arena;
  // List of free elements. The list can be threaded between different arenas
  // depending on the deallocation pattern.
  PoolItem<T> *free_list;
};