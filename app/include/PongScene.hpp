#pragma once

#include <Engine/Common/Manager.hpp>
#include <Engine/IScene.hpp>

/**
 * @brief Example of a custom IScene
 */
class PongScene : public IScene {
public:
  void preload();
  void create();
  void update(double deltaTime);

private:
  Entity player1, player2, ball;
  std::vector<Entity> entitiesQuery;
};