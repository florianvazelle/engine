#pragma once

#include <Engine/Scene.hpp>

class PongScene : public Scene {
public:
  void preload();
  void create();
  void update(double deltaTime);
};