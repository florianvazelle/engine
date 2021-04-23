#pragma once

#include <Engine/Event/Collide.hpp>
#include <Engine/System/ISystem.hpp>

/**
 * @brief Example of a custom ISystem
 */
class BallSystem final : public ISystem {
 public:
  RTTI_DECLARATION
  ~BallSystem() {}

  void onCollide(Collide* collide);
  void update() const;
};