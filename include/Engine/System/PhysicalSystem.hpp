#pragma once

#include <Engine/System/System.hpp>

class PhysicalSystem : public System {
public:
  void update(double deltaTime);
};