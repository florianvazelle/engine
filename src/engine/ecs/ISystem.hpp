#pragma once

#include <engine/meta/RTTI.hpp>

/**
 * @brief ISystem is a pure interface
 */
class ISystem {
 public:
  RTTI_DEFINITION_BASE(ISystem)
  virtual void update() const = 0;
  virtual ~ISystem() = default;
};