#pragma once

#include <engine/engine.hpp>

/**
 * @brief Example of a custom IComponent
 */
class BallRenderer final : public IRenderer {
 public:
  RTTI_DEFINITION(BallRenderer, IRenderer)
  ~BallRenderer(){};

  void render(const Entity& entity);
};