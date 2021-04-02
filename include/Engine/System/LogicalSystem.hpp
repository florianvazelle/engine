#pragma once

#include <vector>

#include <Engine/Common/Entity.hpp>
#include <Engine/System/System.hpp>

class LogicalSystem : public System {
public:
  LogicalSystem() : entitiesQuery(MAX_ENTITIES) {}

  std::vector<Entity> entitiesQuery;

  void update(double deltaTime);
};