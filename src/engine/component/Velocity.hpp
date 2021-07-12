#pragma once

#include <engine/component/Transform.hpp>
#include <engine/ecs/IComponent.hpp>

/**
 * @brief Add Velocity to an Entity, add Physical to this Entity
 */
class Velocity final : public IComponent {
 public:
  RTTI_DEFINITION(Velocity, IComponent)
  float4 direction;

  Velocity() : direction(0, 0, 0, 1) {}
};