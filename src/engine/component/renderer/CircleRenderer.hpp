#pragma once

#include <engine/core/Context.hpp>
#include <engine/core/Window.hpp>
#include <engine/ecs/IComponent.hpp>

class CircleRenderer final : public IComponent {
  RTTI_DEFINITION(CircleRenderer, IComponent)
};