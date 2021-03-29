#pragma once

#include <memory>

#include <Engine/Scene.hpp>
#include <Engine/System/System.hpp>

class Game {
public:
  Game() = delete;
  Game(std::shared_ptr<Scene> scene);

  void preload();
  void run();

private:
  std::shared_ptr<Scene> scene;
  std::vector<std::shared_ptr<System>> systems;
};