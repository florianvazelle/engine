#pragma once

#include <memory>
#include <type_traits>

// to allocate pools of object
template <typename T> struct minipool {

};

template <typename T> union minipool_item {
    public:
        // Methods for the list of free items.
        minipool_item *get_next_item() const { return next; }
        void set_next_item(minipool_item *n) { next = n; }

        // Methods for the storage of the item.
        T *get_storage() { return reinterpret_cast<T *>(datum); }

        // Given a T* cast it to a minipool_item*
        static minipool_item *storage_to_item(T *t) {
            minipool_item *current_item = reinterpret_cast<minipool_item *>(t);
            return current_item;
        }
        
    private:
        using StorageType = typename std::aligned_storage<sizeof(T), alignof(T)>::type; //char[sizeof(T)]; // alignas(alignof(T)) char[sizeof(T)]
        // Points to the next freely available item.
        minipool_item *next;
        // Storage of the item. Note that this is a union
        // so it is shared with the pointer "next" above.
        StorageType datum;
}; // minipool_item

template <typename T> struct minipool_arena {
    private:
        // Storage of this arena.
        std::unique_ptr<minipool_item<T>[]> storage;
        // Pointer to the next arena.
        std::unique_ptr<minipool_arena> next;
        // Creates an arena with arena_size items.
        minipool_arena(size_t arena_size) : storage(new minipool_item[arena_size]) {
            for (size_t i = 1; i < arena_size; i++) {
                storage[i - 1].set_next_item(&storage[i]);
            }
            storage[arena_size - 1].set_next_item(nullptr);
        }
        // Returns a pointer to the array of items. This is used by the arena
        // itself. This is only used to update free_list during initialization
        // or when creating a new arena when the current one is full.
        minipool_item *get_storage() const { return storage.get(); }
        // Sets the next arena. Used when the current arena is full and
        // we have created this one to get more storage.
        void set_next_arena(std::unique_ptr<minipool_arena> &&n) {
            assert(!next);
            next.reset(n.release());
        }
}; // minipool_arena