#pragma once

#include <Engine/System/System.hpp>

class LogicalSystem : public System {
public:
  void update(double deltaTime);
};