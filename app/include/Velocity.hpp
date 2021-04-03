#pragma once

#include <Engine/Component/Component.hpp>

/**
 * @brief Example of a custom Component
 */
class Velocity : public Component {
public:
  RTTI_DECLARATION(Velocity)
  float x, y, z, padding;
};