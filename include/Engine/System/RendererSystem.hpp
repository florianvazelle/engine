#pragma once

#include <Engine/System/System.hpp>

class RendererSystem : public System {
public:
  void update(double deltaTime);
};