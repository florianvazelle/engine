#pragma once

#include <Engine/Component/Transform.hpp>
#include <Engine/Event/IEvent.hpp>
#include <Engine/Event/KeyDown.hpp>
#include <Engine/Event/KeyUp.hpp>
#include <Engine/System/ISystem.hpp>

class BarSystem final : public ISystem {
 public:
  RTTI_DECLARATION
  ~BarSystem() {}

  void update() const;

  void onKeyDown(const IEvent& keyDown);
  void onKeyUp(const IEvent& keyUp);

 private:
  enum MoveDirection { NORTH, SOUTH, STOPPED };

  MoveDirection player1_movement = BarSystem::MoveDirection::STOPPED,
                player2_movement = BarSystem::MoveDirection::STOPPED;

  float4 computeDirection(const MoveDirection& movement, float& y) const;
};