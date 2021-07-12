#pragma once

#include <engine/ecs/IComponent.hpp>
#include <engine/core/Context.hpp>
#include <engine/core/Window.hpp>

class CircleRenderer final : public IComponent {
  RTTI_DEFINITION(CircleRenderer, IComponent)
};