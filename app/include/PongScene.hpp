#pragma once

#include <Engine/Scene.hpp>
#include <Engine/Common/EntityManager.hpp>
#include <Ball.hpp>
#include <Bar.hpp>

class PongScene : public Scene {
public:
  void preload();
  void create();
  void update(double deltaTime);
  void destroy();

private:
  Bar *player1, *player2;
  Ball* ball;
};