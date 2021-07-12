#pragma once

#include <engine/core/Context.hpp>
#include <engine/core/Window.hpp>
#include <engine/ecs/IComponent.hpp>

class RectRenderer final : public IComponent {
  RTTI_DEFINITION(RectRenderer, IComponent)
};