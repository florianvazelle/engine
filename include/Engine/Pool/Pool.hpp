#pragma once

#include <iostream>

#include <Engine/Common/Log.hpp>
#include <Engine/Pool/Arena.hpp>
#include <Engine/Pool/PoolItem.hpp>

class IPool {
public:
  virtual ~IPool() = default;
};

/**
 * @brief Une Pool alloue des objets pour une utilisation ultérieure
 */
template <typename T> class Pool : public IPool {
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
    assert(free_list == nullptr && "Unable to get more object from the pool, Arena is full.");

    // Get the first free item.
    PoolItem<T> *current_item = free_list;
    // Update the free list to the next free item.
    free_list = current_item->get_next_item();

    return set_storage(current_item, std::forward<Args>(args)...);
  }

  template <typename... Args> T *alloc_with_id(const uint32_t &id, Args &&... args) {
    PoolItem<T> *current_item = this->at(id);

    // Mis a jour de la free_list
    if (free_list != nullptr) {
      // Si le début de la free_list correspond à mon current_item, comportement normal
      if (free_list == current_item) {
        // Update the free list to the next free item.
        free_list = current_item->get_next_item();
      } else {
        // Sinon je vérifie que mon current_item ne soit pas dans la free list
        PoolItem<T> *tmp = free_list;
        // On parcours la free list, jusqu'a la fin
        do {
          // Si mon current_item correspond
          if (current_item == tmp->get_next_item()) {
            // On l'enlève de la free list
            tmp->set_next_item(current_item->get_next_item());
            break;
          }
          tmp = tmp->get_next_item();
        } while (tmp != nullptr);
      }
    }

    // Si la free list est vide, on remplace directement l'élément qui nous intérésse

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
    PoolItem<T> *current_item = PoolItem<T>::storage_to_item(t);
    current_item->is_set      = false;

    // Add the item at the beginning of the free list.
    current_item->set_next_item(free_list);
    free_list = current_item;
  }

  void free_with_id(const uint32_t &id) { free(this->at(id)->get_storage()); }

  typedef PoolItem<T> *iterator;

  iterator begin() {
    PoolItem<T> *current_item = arena->get_storage();
    if (!current_item->is_set) return next(current_item);
    return current_item;
  }

  iterator end() { return begin() + arena_size; }

  // TODO : we can override operator++
  iterator next(iterator item) {
    PoolItem<T> *current_item = item->get_next_item();
    if (current_item == nullptr) return end();

    while (!current_item->is_set) {
      current_item = current_item->get_next_item();
      if (current_item == nullptr) return end();
    }

    return current_item;
  }

  PoolItem<T> *at(const uint32_t &id) {
    assert(id < arena_size && "Pool out of range.");
    return arena->get_storage() + id;
  }

  PoolItem<T> *at(const uint32_t &id) const { return this->at(id); }

  T &operator[](const uint32_t &id) { return this->at(id)->get_storage(); }
  T &operator[](const uint32_t &id) const { return this->at(id)->get_storage(); }

private:
  // Size of the arenas created by the pool.
  size_t arena_size;

  // Current arena. Changes when it becomes full and we want to allocate one
  // more object.
  std::unique_ptr<Arena<T>> arena;

  // List of free elements. The list can be threaded between different arenas
  // depending on the deallocation pattern.
  PoolItem<T> *free_list;

  template <typename... Args> T *set_storage(PoolItem<T> *current_item, Args &&... args) {
    // Get the storage for T.
    T *result            = current_item->get_storage();
    current_item->is_set = true;

    // Construct the object in the obtained storage.
    new (result) T(std::forward<Args>(args)...);

    return result;
  }
};