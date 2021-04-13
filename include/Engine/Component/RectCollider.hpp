#pragma once

#include <Engine/Component/ICollider.hpp>

class RectCollider : public ICollider {
 public:
  RTTI_DECLARATION
  ~RectCollider(){};

  bool intersect(const Entity& e1, const Entity& e2);
};