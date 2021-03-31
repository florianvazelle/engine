#pragma once

#include <Engine/Common/EntityManager.hpp>
#include <Engine/Scene.hpp>

class PongScene : public Scene {
public:
  void preload();
  void create();
  void update(double deltaTime);
  void destroy();

private:
  Entity *player1, *player2, *ball;
};