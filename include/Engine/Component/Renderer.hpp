#pragma once

#include <Engine/Component/Component.hpp>

class Renderer : public Component {
public:
  void update(double deltaTime);
  std::string name() { return "renderer"; }
};