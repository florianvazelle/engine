#pragma once

#include <Engine/Component/Component.hpp>

class Renderer : public Component {
public:
  RTTI_DECLARATION
  void update(double deltaTime);
};