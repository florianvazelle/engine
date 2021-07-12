#pragma once

#include <engine/ecs/Entity.hpp>
#include <engine/ecs/IComponent.hpp>

class ICollider : public IComponent {
 public:
  RTTI_DEFINITION(ICollider, IComponent)
  virtual void intersect(const Entity& e1, const Entity& e2) const = 0;
  virtual ~ICollider() = default;
};