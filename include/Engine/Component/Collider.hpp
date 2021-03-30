#pragma once

#include <Engine/Component/Transform.hpp>

class Collider : public Component {
public:
  bool intersect(Transform trans);

  std::string name() { return "collider"; }
};