#pragma once

#include <Engine/Common/Entity.hpp>
#include <Engine/System/ISystem.hpp>
#include <vector>

class LogicalSystem : public ISystem {
 public:
  RTTI_DECLARATION
  ~LogicalSystem() {}

  void update() const;
};