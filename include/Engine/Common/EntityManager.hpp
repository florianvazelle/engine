#pragma once

#include <atomic>
#include <mutex>

#include <Engine/Common/EntityFactory.hpp>

/**
 * Thread-safe Singleton, to return a EntityFactory
 */
class EntityManager {
public:
  static EntityFactory* GetInstance();

private:
  EntityManager() = default;

  static std::atomic<EntityFactory*> s_instance;
  static std::mutex s_mutex;
};

EntityFactory* EntityManager::GetInstance() {
  EntityFactory* p = s_instance.load(std::memory_order_acquire);
  if (p == nullptr) {  // 1st check
    std::lock_guard<std::mutex> lock(s_mutex);
    p = s_instance.load(std::memory_order_relaxed);
    if (p == nullptr) {  // 2nd (double) check
      p = new EntityFactory();
      s_instance.store(p, std::memory_order_release);
    }
  }
  return p;
}