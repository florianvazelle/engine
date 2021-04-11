#pragma once

#include <Engine/Component/IRenderer.hpp>

class BallRenderer final : public IRenderer {
 public:
  RTTI_DECLARATION
  ~BallRenderer(){};

  void render(const Context& context, const Entity& entity);
};