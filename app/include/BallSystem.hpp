#pragma once

#include <vector>

#include <Engine/Common/Entity.hpp>
#include <Engine/System/System.hpp>

/**
 * @brief Example of a custom System
 */
class BallSystem : public System {
public:
  RTTI_DECLARATION(BallSystem)

  ThreadPool thread_pool;
  std::vector<Entity> entitiesQuery;
  std::vector<std::future<void>> results;

  BallSystem() : System(), entitiesQuery(MAX_ENTITIES), thread_pool(num_threads), results(MAX_ENTITIES) {}

  void update(double deltaTime);
};