#pragma once

#include <Engine/Component/IRenderer.hpp>

class BarRenderer final : public IRenderer {
 public:
  RTTI_DECLARATION
  ~BarRenderer(){};

  void render(const Entity& entity);
};