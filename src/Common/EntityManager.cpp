#include <Engine/Common/EntityManager.hpp>

std::atomic<EntityFactory*> EntityManager::s_instance{nullptr};
std::mutex EntityManager::s_mutex;

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
