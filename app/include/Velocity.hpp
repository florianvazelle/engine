#pragma once

#include <Engine/Component/Component.hpp>
#include <Engine/Component/Transform.hpp>

/**
 * @brief Example of a custom Component
 */
class Velocity : public Component {
public:
  RTTI_DECLARATION(Vecity)
  float4 direction;

  Velocity() : direction(0, 0, 0, 1) {}
};