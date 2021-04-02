#pragma once

#include <Engine/Component/Component.hpp>

// We need to define us custom Component here !
#define EXTRA_COMPONENTS Velocity

/**
 * @brief Example of a custom Component
 */
class Velocity : public Component {
public:
  RTTI_DECLARATION(Velocity)
  float x, y, z, padding;
};