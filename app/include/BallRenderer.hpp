#pragma once

#include <Engine/Component/IRenderer.hpp>

/**
 * @brief Example of a custom IComponent
 */
class BallRenderer final : public IRenderer {
 public:
  RTTI_DECLARATION
  ~BallRenderer(){};

  void render(const Context& context, const Entity& entity);
};