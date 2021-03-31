#pragma once

#include <Engine/Component/Component.hpp>

class Velocity : public Component {
public:
  RTTI_DECLARATION(Velocity)
  float x, y, z, padding;
};