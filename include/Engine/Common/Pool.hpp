#pragma once

#include <cassert>
#include <iostream>
#include <memory>
#include <type_traits>

// A pool allocate objects for later use
template <typename T> struct Pool {
  // Pool items store each element of an arena
  union Pool_item {
  public:
    // Methods for the list of free items.
    Pool_item *get_next_item() const { return next; }
    void set_next_item(Pool_item *n) { next = n; }

    // Methods for the storage of the item.
    T *get_storage() { return reinterpret_cast<T *>(&datum); }

    // Given a T* cast it to a Pool_item*
    static Pool_item *storage_to_item(T *t) {
      Pool_item *current_item = reinterpret_cast<Pool_item *>(t);
      return current_item;
    }

struct Pool_arena {
    private:
        // Storage of this arena.
        std::unique_ptr<Pool_item[]> storage;
        // Pointer to the next arena.
        std::unique_ptr<Pool_arena> next;
        // Creates an arena with arena_size items.
    
    public:
        // Constructor allocate a pool item with the arena size
        Pool_arena(size_t arena_size) : storage(new Pool_item[arena_size]) {
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
        Pool_item *get_storage() const { return storage.get(); }

        // TO DELETE
        // Sets the next arena. Used when the current arena is full and
        // we have created this one to get more storage.
        // void set_next_arena(std::unique_ptr<Pool_arena> &&n) {
        //     assert(!next);
        //     next.reset(n.release());
        // }
}; // Pool_arena

  struct Pool_arena {
  private:
    // Storage of this arena.
    std::unique_ptr<Pool_item[]> storage;
    // Pointer to the next arena.
    std::unique_ptr<Pool_arena> next;
    // Creates an arena with arena_size items.

  public:
    Pool_arena(size_t arena_size) : storage(new Pool_item[arena_size]) {
      for (size_t i = 1; i < arena_size; i++) {
        storage[i - 1].set_next_item(&storage[i]);
      }
      storage[arena_size - 1].set_next_item(nullptr);
    }
    // Returns a pointer to the array of items. This is used by the arena
    // itself. This is only used to update free_list during initialization
    // or when creating a new arena when the current one is full.
    Pool_item *get_storage() const { return storage.get(); }
    // Sets the next arena. Used when the current arena is full and
    // we have created this one to get more storage.
    void set_next_arena(std::unique_ptr<Pool_arena> &&n) {
      assert(!next);
      next.reset(n.release());
    }
  };  // Pool_arena

    // Allocates an object in the current arena. 
    template <typename... Args> T *alloc(Args &&... args) {
        // TO DELETE
        if (free_list == nullptr) {
            std::cout << "Unable to get more object from the pool, Arena is full" << std::endl;
            return nullptr;
            // // If the current arena is full, create a new one.
            // std::unique_ptr<Pool_arena> new_arena(new Pool_arena(arena_size));
            // // Link the new arena to the current one.
            // new_arena->set_next_arena(std::move(arena));
            // // Make the new arena the current one.
            // arena.reset(new_arena.release());
            // // Update the free_list with the storage of the just created arena.
            // free_list = arena->get_storage();
        }

  // Creates a new pool that will use arenas of arena_size.
  Pool(size_t arena_size)
      : arena_size(arena_size), arena(new Pool_arena(arena_size)), free_list(arena->get_storage()) {}

  // Allocates an object in the current arena.
  template <typename... Args> T *alloc(Args &&... args) {
    if (free_list == nullptr) {
      // If the current arena is full, create a new one.
      std::unique_ptr<Pool_arena> new_arena(new Pool_arena(arena_size));
      // Link the new arena to the current one.
      new_arena->set_next_arena(std::move(arena));
      // Make the new arena the current one.
      arena.reset(new_arena.release());
      // Update the free_list with the storage of the just created arena.
      free_list = arena->get_storage();
    }

    // Get the first free item.
    Pool_item *current_item = free_list;
    // Update the free list to the next free item.
    free_list = current_item->get_next_item();

    // Get the storage for T.
    T *result = current_item->get_storage();
    // Construct the object in the obtained storage.
    new (result) T(std::forward<Args>(args)...);

        // Add the item at the beginning of the free list.
        current_item->set_next_item(free_list);
        free_list = current_item;
    }

    public:
        ~Pool(){
            Pool_item *s = arena->get_storage();
            for(int i = 0; i < arena_size; ++i){
                free((s+i)->get_storage());
            }
        }
}; // Pool

  void free(T *t) {
    // Destroy the object.
    t->T::~T();

    // Convert this pointer to T to its enclosing pointer of an item of the
    // arena.
    Pool_item *current_item = Pool_item::storage_to_item(t);

    // Add the item at the beginning of the free list.
    current_item->set_next_item(free_list);
    free_list = current_item;
  }

  typedef T *iterator;
  typedef const T *const_iterator;

  iterator begin() { return (arena->get_storage()->get_storage()); }
  const_iterator begin() const { return (arena->get_storage()->get_storage()); }
  iterator end() { return (free_list->get_storage()); }
  const_iterator end() const { return (free_list->get_storage()); }
};  // Pool

void testPools();