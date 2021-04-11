#pragma once

#include <Engine/Common/Manager.hpp>
#include <Engine/Scene.hpp>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

/**
 * @brief Example of a custom Scene
 */
class PongScene final : public Scene {
 public:
  void preload();
  void create();
};