#pragma once

#include <Engine/Common/Entity.hpp>
#include <Engine/Component/Collider.hpp>
#include <Engine/Component/Renderer.hpp>
#include <Engine/Component/Transform.hpp>

struct Ball : public Entity {
public:
  RTTI_DECLARATION
  Ball() : trans(), coll(), rend(), Entity(&trans, &coll, &rend) {}

  Transform trans;
  Collider coll;
  Renderer rend;
};