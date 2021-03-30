#pragma once

#include <Engine/Component/Component.hpp>

class Velocity : public Component {
public:
  RTTI_DECLARATION
  float x, y, z, padding;
};