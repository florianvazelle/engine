#pragma once

#include <Engine/System/System.hpp>

class RendererSystem : public System {
public:
  RTTI_DECLARATION(RendererSystem)

  void update(double deltaTime);
};