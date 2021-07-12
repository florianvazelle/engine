#pragma once

#include <engine/engine.hpp>

class BarRenderer final : public IRenderer {
 public:
  RTTI_DEFINITION(BarRenderer, IRenderer)
  ~BarRenderer(){};

  void render(const Entity& entity);
};