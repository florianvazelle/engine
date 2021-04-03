#pragma once

#include <Engine/Common/Manager.hpp>
#include <Engine/Scene.hpp>

/**
 * @brief Example of a custom Scene
 */
class PongScene : public Scene {
public:
  void preload();
  void create();

private:
  Entity player1, player2, ball;
};