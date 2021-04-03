#pragma once

#include <vector>

#include <Engine/Common/Entity.hpp>
#include <Engine/System/System.hpp>

class LogicalSystem : public System {
public:
  RTTI_DECLARATION(LogicalSystem)

  void update(double deltaTime);
};