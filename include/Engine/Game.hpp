#pragma once

#include <memory>

#include <Engine/Core/Context.hpp>
#include <Engine/Scene.hpp>
#include <Engine/System/System.hpp>

class Game {
public:
  Game() = delete;
  Game(std::shared_ptr<Scene> scene);

  void preload();
  void update();
  void run();

private:
  std::shared_ptr<Scene> scene;
  Context context;
};