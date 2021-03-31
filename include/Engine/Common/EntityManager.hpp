#pragma once

#include <atomic>
#include <map>
#include <mutex>
#include <vector>

#include <Engine/Common/EntityFactory.hpp>
#include <Engine/Common/RTTI.hpp>

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