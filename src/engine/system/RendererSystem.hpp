#pragma once

#include <SDL2/SDL2_gfxPrimitives.h>
#include <stdio.h>
#include <stdlib.h>

#include <engine/component/renderer/CircleRenderer.hpp>
#include <engine/component/renderer/RectRenderer.hpp>
#include <engine/core/Context.hpp>
#include <engine/core/Window.hpp>
#include <engine/ecs/ISystem.hpp>
#include <engine/meta/Log.hpp>

class RendererSystem : public ISystem {
 public:
  RTTI_DEFINITION(RendererSystem, ISystem)
  ~RendererSystem() {}

  void update() const {
    LOG(LOG_INFO, "[RendererSystem] Update!");
    /**
     * @todo Mettre ici le rendu: seuls les objets visibles méritent d’être
     * affiché. Attention il faut parfois aussi tenir compte des objets hors
     * champs (ombres et lumières, partiellement visibles...)
     */

    Context* context = Context::GetInstance();

    // Flush renderer.
    SDL_SetRenderDrawColor(context->window()->renderer(), 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(context->window()->renderer());

    Registry* registry = Registry::GetInstance();

    // *** RectRenderer ***
    {
      registry->GetEntitiesWithTags(registry->entitiesQuery, RectRenderer::rtti);

      registry->results.resize(registry->entitiesQuery.size());
      for (unsigned int i = 0; i < registry->entitiesQuery.size(); i++) {
        registry->results[i] = registry->threadPool.push(
            [&](const Entity& entity) {
              const Transform* const trans = registry->GetComponent<Transform>(entity);

              float x = trans->x();
              float y = trans->y();
              float4 size = trans->size();

              // First we set the rectangle fill colour to that of the spritecomponents.
              SDL_SetRenderDrawColor(context->window()->renderer(), 255.f, 255.f, 255.f, 255.f);

              // Then we create the actual rectangle.
              const SDL_Rect draw_rect = {static_cast<int>(x), static_cast<int>(y),
                                          static_cast<int>(size.x), static_cast<int>(size.y)};

              // Now the rectangle gets renderered with the appropriate colours and position
              // data to the window.
              SDL_RenderFillRect(context->window()->renderer(), &draw_rect);
            },
            registry->entitiesQuery[i]);
      }
    }

    // *** CircleRenderer ***
    {
      registry->GetEntitiesWithTags(registry->entitiesQuery, CircleRenderer::rtti);

      registry->results.resize(registry->entitiesQuery.size());
      for (unsigned int i = 0; i < registry->entitiesQuery.size(); i++) {
        registry->results[i] = registry->threadPool.push(
            [&](const Entity& entity) {
              const Transform* const trans = registry->GetComponent<Transform>(entity);

              float x = trans->x();
              float y = trans->y();
              float4 size = trans->size();

              // We use SDL2_gfx to make drawing circles easier.
              filledCircleRGBA(context->window()->renderer(), x, y, size.x, 255.f, 255.f, 255.f,
                               255.f);
            },
            registry->entitiesQuery[i]);
      }
    }

    for (auto&& result : registry->results) result.get();

    // Draw everything.
    SDL_RenderPresent(context->window()->renderer());
  }
};