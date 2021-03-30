#pragma once

#include <Engine/Component/Transform.hpp>

class Collider : public Component {
public:
  RTTI_DECLARATION
  bool intersect(Transform trans);
};