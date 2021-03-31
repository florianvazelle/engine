#pragma once

#include <Engine/Component/Component.hpp>

class Renderer : public Component {
public:
  RTTI_DECLARATION(Renderer)
  void update(double deltaTime);
};