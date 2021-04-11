#pragma once

#include <Engine/System/ISystem.hpp>

class PhysicalSystem : public ISystem {
 public:
  RTTI_DECLARATION
  ~PhysicalSystem() {}

  void update(Context& context);
};