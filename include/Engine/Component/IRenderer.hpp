#pragma once

#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_render.h>

#include <Engine/Component/IComponent.hpp>
#include <Engine/Core/Context.hpp>

/**
 * @brief IRenderer is a pure interface
 */
class IRenderer : public IComponent {
 public:
  RTTI_DECLARATION
  virtual void render(const Entity& entity) = 0;  // pure virtual functions
  // ...
  // ... no data members ...
  // ...
  virtual ~IRenderer() = default;
};