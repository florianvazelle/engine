#pragma once

#include <vector>

#include <Engine/System/System.hpp>
#include <Engine/Common/Entity.hpp>

class LogicalSystem : public System {
public:
  LogicalSystem() : entitiesQuery(MAX_ENTITIES) {}

  std::vector<Entity*> entitiesQuery;

  void update(double deltaTime);
};