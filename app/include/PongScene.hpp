#pragma once

#include <Engine/Common/EntityFactory.hpp>
#include <Engine/Scene.hpp>

#include <Ball.hpp>
#include <Bar.hpp>

class PongScene : public Scene {
public:
  void preload();
  void create();
  void update(double deltaTime);
  void destroy();

private:
  EntityFactory obdb;

  Bar *player1, *player2;
  Ball* ball;
};