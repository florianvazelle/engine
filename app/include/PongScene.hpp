#pragma once

#include <Engine/Common/Manager.hpp>
#include <Engine/IScene.hpp>

class PongScene : public IScene {
public:
  void preload();
  void create();
  void update(double deltaTime);

private:
  Entity player1, player2, ball;
};