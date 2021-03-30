#pragma once

#include <Engine/Common/Matrix.hpp>
#include <Engine/Component/Component.hpp>

class Velocity : public Component {
public:
  RTTI_DECLARATION
  float x, y, z, padding;
};