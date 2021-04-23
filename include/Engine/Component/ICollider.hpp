#pragma once

#include <Engine/Component/Transform.hpp>
#include <Engine/Pool/Pool.hpp>

class ICollider : public IComponent {
 public:
  RTTI_DECLARATION
  virtual void intersect(const Entity& e1, const Entity& e2) = 0;
  virtual ~ICollider() = default;
};