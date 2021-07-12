#pragma once

#include <atomic>
#include <mutex>

/**
 * @brief Thread-safe Singleton
 *
 * https://stackoverflow.com/questions/34519073/inherit-singleton
 */
template <typename T>
class Singleton {
 public:
  /**
   * @brief Retourne une unique instance de T (double-check locking)
   */
  static T* GetInstance() noexcept(std::is_nothrow_constructible<T>::value);

 protected:
  Singleton() noexcept = default;
  Singleton(const Singleton&) = delete;
  Singleton& operator=(const Singleton&) = delete;
  virtual ~Singleton() = default;  // to silence base class Singleton<T> has a
                                   // non-virtual destructor [-Weffc++]

  static std::atomic<T*> s_instance;
  static std::mutex s_mutex;
};

template <typename T>
std::atomic<T*> Singleton<T>::s_instance{nullptr};

template <typename T>
std::mutex Singleton<T>::s_mutex;

template <typename T>
T* Singleton<T>::GetInstance() noexcept(
    std::is_nothrow_constructible<T>::value) {
  T* p = s_instance.load(std::memory_order_acquire);
  if (p == nullptr) {  // 1st check
    std::lock_guard<std::mutex> lock(s_mutex);
    p = s_instance.load(std::memory_order_relaxed);
    if (p == nullptr) {  // 2nd (double) check
      p = new T();
      s_instance.store(p, std::memory_order_release);
    }
  }
  return p;
}