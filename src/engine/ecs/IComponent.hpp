#pragma once

#include <engine/meta/RTTI.hpp>

/**
 * @brief IComponent is a pure interface
 */
class IComponent {
 public:
  RTTI_DEFINITION_BASE(IComponent)
  virtual ~IComponent() = default;
};