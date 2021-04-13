#pragma once

#include <Engine/Component/IComponent.hpp>
#include <Engine/Component/Transform.hpp>

/**
 * @brief Add Velocity to an Entity, add Physical to this Entity
 */
class Velocity final : public IComponent {
 public:
  RTTI_DECLARATION
  float4 direction;

  Velocity() : direction(0, 0, 0, 1) {}
};