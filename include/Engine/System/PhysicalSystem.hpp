#pragma once

#include <Engine/System/System.hpp>

class PhysicalSystem : public System {
public:
  RTTI_DECLARATION(PhysicalSystem)

  void update(double deltaTime);
};