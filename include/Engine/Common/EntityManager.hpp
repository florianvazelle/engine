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