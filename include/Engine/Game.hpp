#pragma once

#include <Engine/Core/Context.hpp>
#include <Engine/Scene.hpp>
#include <Engine/System/ISystem.hpp>
#include <memory>
#include <string>

class Game {
 public:
  Game() = delete;
  Game(Game& game) = delete;
  Game(std::string title, const int w, const int h, std::uint32_t flags);
  ~Game();

  void run(const std::shared_ptr<Scene>& scene);
};