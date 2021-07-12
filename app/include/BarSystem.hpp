#pragma once

#include <engine/engine.hpp>

class BarSystem final : public ISystem {
 public:
  RTTI_DEFINITION(BarSystem, ISystem)
  ~BarSystem() {}

  void update() const;

  void onKeyDown(KeyDown* keyDown);
  void onKeyUp(KeyUp* keyUp);

 private:
  enum MoveDirection { NORTH, SOUTH, STOPPED };

  MoveDirection player1_movement = BarSystem::MoveDirection::STOPPED,
                player2_movement = BarSystem::MoveDirection::STOPPED;

  float4 computeDirection(const MoveDirection& movement, float& y) const;
};