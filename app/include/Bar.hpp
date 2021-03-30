#pragma once

#include <Engine/Component/Collider.hpp>
#include <Engine/Component/Renderer.hpp>
#include <Engine/Component/Transform.hpp>

struct Bar : public Entity {
public:
  Bar() : trans(), coll(), rend(), Entity(&trans, &coll, &rend) {}

  Transform trans;
  Collider coll;
  Renderer rend;
};