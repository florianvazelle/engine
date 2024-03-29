#pragma once

#include <engine/engine.hpp>

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