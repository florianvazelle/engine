#pragma once

#include <Engine/Component/Transform.hpp>
#include <Engine/Pool/Pool.hpp>

class Collider : public IComponent {
 public:
  RTTI_DECLARATION
  bool intersect(Transform trans);
};