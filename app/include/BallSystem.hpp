#pragma once

#include <Engine/System/ISystem.hpp>

/**
 * @brief Example of a custom ISystem
 */
class BallSystem final : public ISystem {
 public:
  RTTI_DECLARATION
  ~BallSystem() {}

  void update() const;
};