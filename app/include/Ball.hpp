#pragma once

#include <Engine/Common/Entity.hpp>
#include <Engine/Component/Collider.hpp>
#include <Engine/Component/Renderer.hpp>
#include <Engine/Component/Transform.hpp>
#include <Engine/Component/Velocity.hpp>

struct Ball : public Entity {
public:
  RTTI_DECLARATION
  Ball() : trans(), velo(), coll(), rend(), Entity(&trans, &velo, &coll, &rend) {}

  Transform trans;
  Velocity velo;
  Collider coll;
  Renderer rend;
};