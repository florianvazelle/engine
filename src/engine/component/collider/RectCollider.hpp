#pragma once

#include <engine/ecs/IComponent.hpp>

class RectCollider final : public IComponent {
  RTTI_DEFINITION(RectCollider, IComponent)
};