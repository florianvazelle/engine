#pragma once

#include <Pool.hpp>

class System {
public:
  virtual void update(double deltaTime) = 0;
};