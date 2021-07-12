#pragma once

#include <engine/engine.hpp>

/**
 * @brief Example of a custom ISystem
 */
class BallSystem final : public ISystem {
 public:
  RTTI_DEFINITION(BallSystem, ISystem)
  ~BallSystem() {}

  void onCollide(Collide* collide);
  void update() const;
};