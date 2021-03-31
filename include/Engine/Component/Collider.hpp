#pragma once

#include <Engine/Component/Transform.hpp>
#include <Engine/Pool/Pool.hpp>

class Collider : public Component {
public:
  RTTI_DECLARATION(Collider)
  bool intersect(Transform trans);
};