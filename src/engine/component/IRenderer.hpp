#pragma once

#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_render.h>

#include <engine/core/Context.hpp>
#include <engine/ecs/Entity.hpp>
#include <engine/ecs/IComponent.hpp>

/**
 * @brief IRenderer is a pure interface
 */
class IRenderer : public IComponent {
 public:
  RTTI_DEFINITION(IRenderer, IComponent)
  virtual void render(const Entity& entity) = 0;
  virtual ~IRenderer() = default;
};