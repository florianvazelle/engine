#pragma once

#include <memory>

#include <Engine/Core/Context.hpp>
#include <Engine/IScene.hpp>
#include <Engine/System/System.hpp>

class Game {
public:
  Game() = delete;
  Game(std::shared_ptr<IScene> scene);

  void preload();
  void update();
  void run();

private:
  std::shared_ptr<IScene> scene;
  Context context;
};