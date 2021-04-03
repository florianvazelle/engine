#pragma once

#include <Engine/Component/Component.hpp>

/**
 * @brief Example of a custom Component
 */
class Velocity : public Component {
public:
  RTTI_DECLARATION(Vecity)
  float x, y, z, w;  // direction

  Velocity() : x(0), y(0), z(0), w(1) {}
};